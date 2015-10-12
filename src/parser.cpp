#include <cassert>

#include "parser.hpp"
#include "job.hpp"
#include "context.hpp"
#include "permutation.hpp"
#include "state_machine.hpp"

namespace parlex {

parser::parser(int threadCount) : activeCount(0), terminating(false) {
	for (; threadCount > 0; --threadCount) {
		workers.emplace_back([=]() {
			std::unique_lock<std::mutex> lock(mutex);
			goto wait;
			while (!terminating) {
				{
					std::tuple<details::context, int> & item = work.front();
					work.pop();
					lock.unlock();
					auto const & context = std::get<0>(item);
					auto const nextDfaState = std::get<1>(item);
					context.owner().machine.process(context, nextDfaState);
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

abstract_syntax_graph parser::parse(recognizer const & r, std::u32string const & document) {
	details::job j(*this, document, r);
	std::unique_lock<std::mutex> lock(mutex);
	while (activeCount != 0) {
		halt_cv.wait(lock);
		if (handle_deadlocks(j)) {
			break;
		}
	};
	return construct_result(j, details::match(details::match_class(r, 0), document.size()));
}

void parser::schedule(details::context context, int nextDfaState) {
	/*
	std::unique_lock<std::mutex> lock(mutex);
	activeCount++;
	work.emplace(std::make_tuple(context, nextDfaState));
	work_cv.notify_one();
	/*/
	context.owner().machine.process(context, nextDfaState);
	//*/
}

abstract_syntax_graph parser::construct_result(details::job const & j, details::match const & match) {
	abstract_syntax_graph result(match);
	for (auto const & pair : j.producers) {
		details::match_class const & matchClass = pair.first;
		details::producer const & producer = *pair.second;
		for (auto const & pair2 : producer.match_to_permutations) {
			details::match const & match = pair2.first;
			std::set<permutation> const & permutations = pair2.second;
			result.table[match] = permutations;
		}
	}
	return result;
}

bool parser::handle_deadlocks(details::job const & j) {
	std::unique_lock<std::mutex> lock(mutex);
	assert(activeCount == 0);
	//todo
	//build a dependency graph and detect cyclical portions that should be halted
	//if no subjobs remain, return true
	return true;
}

}
