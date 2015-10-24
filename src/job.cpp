#include <iostream>

#include "state_machine.hpp"
#include "job.hpp"
#include "terminal.hpp"
#include "context.hpp"
#include "parser.hpp"
#include "token.hpp"

namespace parlex {
namespace details {

job::job(parser & owner, std::u32string const & document, recognizer const & main) :
		owner(owner),
		document(document),
		main(main)
	{
		std::cout << "starting job using " << main.get_id() << std::endl;
		auto & producer = get_producer(match_class(main, 0));
	}



void job::connect(match_class const & matchClass, context_ref const & c, int nextDfaState) {
	get_producer(matchClass).add_subscription(c, nextDfaState);
}

producer & job::get_producer(match_class const & matchClass) {
	std::unique_lock<std::mutex> lock(producers_mutex);
	if (producers.count(matchClass)) {
		return *producers[matchClass];
	} else {
		lock.unlock();
		if (matchClass.r.is_terminal()) {
			terminal const * t = static_cast<terminal const *>(&matchClass.r);
			token * result = new token(*this, *t, matchClass.document_position);
			lock.lock();
			producers.emplace(
				std::piecewise_construct,
				std::forward_as_tuple(matchClass),
				std::forward_as_tuple(result)
			);
		} else {
			state_machine const * machine = static_cast<state_machine const *>(&matchClass.r);
			subjob * result = new subjob(*this, *machine, matchClass.document_position);
			lock.lock();
			auto didEmplace = producers.emplace(
				std::piecewise_construct,
				std::forward_as_tuple(matchClass),
				std::forward_as_tuple(result)
			).second;
			lock.unlock();
			if (didEmplace) {
				result->start();
			}
			lock.lock();
		}
	}
	return *producers[matchClass];
}


}
}
