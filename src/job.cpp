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
		auto & producer = get_producer(match_class(main, 0));
	}



void job::connect(match_class const & matchClass, context const & c, int nextDfaState) {
	get_producer(matchClass).add_subscription(c, nextDfaState);
}

producer & job::get_producer(match_class const & matchClass) {
	std::unique_lock<std::mutex> lock(producers_mutex);
	if (producers.count(matchClass)) {
		return *producers[matchClass];
	} else {
		producer * result = nullptr;
		if (matchClass.r.is_terminal()) {
			terminal const * t = static_cast<terminal const *>(&matchClass.r);
			result = new token(*this, *t, matchClass.document_position);
		} else {
			state_machine const * machine = static_cast<state_machine const *>(&matchClass.r);
			result = new subjob(*this, *machine, matchClass.document_position);
		}
		//producers.emplace_back(std::piecewise_construct, std::forward_as_tuple(matchClass), std::forward_as_tuple(result));
		return *result;
	}
}


}
}
