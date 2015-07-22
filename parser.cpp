#include "parser.hpp"
#include "job.hpp"
#include "parse_context.hpp"

namespace parlex {

parser::parser(int threadCount) {
	for (; threadCount > 0; --threadCount) {
		workers.emplace_back([=]() {
			std::unique_lock<std::mutex> lock(mutex);
			goto wait;			
			while (!terminating) {
				{
					std::pair<details::parse_context, details::match_class> item = work.front();
					work.pop();
					lock.unlock();
					details::parse_context const & context = item.first;
					details::match_class const & matchClass = item.second;
					context.owner->process_state(context.dfa_state, context.current_document_position, context.preceeding_match_classes);
					if (--activeCount == 0) {
						halt_cv.notify_one();
					}
					lock.lock();
				}
wait:
				work_cv.wait(lock, [this]() { return work.size() > 0 && !terminating; });
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
	details::job j(this, document, i->second);
	halt_cv.wait(lock, [this]{ return handle_deadlocks_check_completion(); });
	return construct_result();
}

void parser::schedule(details::parse_context const & context, details::match_class const & matchClass) {
	std::unique_lock<std::mutex> lock(mutex);
	activeCount++;
	work.emplace(context, matchClass);
	work_cv.notify_one();
}

abstract_syntax_graph parser::construct_result(job const & j, match_class const & matchClass) {
	abstract_syntax_graph result(matchClass);
	for (auto const & pair : j.subjobs) {
		match_category const & matchCategory = pair.first;
		subjob const & subJob = pair.second;
		for (auto const & pair2 : subJob.)
	}
}

}