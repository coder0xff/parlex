#include <cassert>

#include "parser.hpp"
#include "job.hpp"
#include "parse_context.hpp"
#include "permutation.hpp"

namespace parlex {

parser::parser(int threadCount) : activeCount(0), terminating(false) {
	for (; threadCount > 0; --threadCount) {
		workers.emplace_back([=]() {
			std::unique_lock<std::mutex> lock(mutex);
			goto wait;			
			while (!terminating) {
				{
					std::pair<details::parse_context, details::match> item = work.front();
					work.pop();
					lock.unlock();
					details::parse_context const & context = item.first;
					details::match const & match = item.second;
					context.owner->process_state(context.dfa_state, context.current_document_position, context.preceeding_matches);
					if (--activeCount == 0) {
						halt_cv.notify_one();
					}
					lock.lock();
				}
wait:
				work_cv.wait(lock, [this]() { return work.size() > 0 || terminating; });
			}
		});
	}
}

parser::~parser() {
	terminating = true;
	work_cv.notify_all();
	for (auto & thread : workers) {
		thread.join();
	}
}

abstract_syntax_graph parser::parse(grammar const & g, std::u32string const & document) {
	std::unique_lock<std::mutex> lock(mutex);
	auto i = g.find("main");
	if (i == g.end()) {
		throw "no main production";
	}
	lock.unlock();
	details::job j(this, document, i->second);
	lock.lock();
	while (activeCount != 0) {
		halt_cv.wait(lock);
		if (handle_deadlocks(j)) {
			break;
		}
	};
	return construct_result(j, details::match(details::match_class(&i->second, 0), document.size()));
}

void parser::schedule(details::parse_context const & context, details::match const & match) {
	activeCount++;
	std::unique_lock<std::mutex> lock(mutex);
	work.emplace(context, match);
	work_cv.notify_one();
}

abstract_syntax_graph parser::construct_result(details::job const & j, details::match const & match) {
	abstract_syntax_graph result(match);
	for (auto const & pair : j.subjobs) {
		details::match_class const & matchClass = pair.first;
		details::subjob const & subJob = pair.second;
		for (auto const & pair2 : subJob.matchToPermutations) {
			details::match const & match = pair2.first;
			std::set<permutation> const & permutations = pair2.second;
			result.table[match] = permutations;
		}
	}
	return result;
}

bool parser::handle_deadlocks(details::job const & j) {
	assert(activeCount == 0);
	return true;
}

}