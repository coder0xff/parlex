#include "state_machine.hpp"
#include "context.hpp"
#include "subjob.hpp"

namespace parlex {

state_machine::state_machine(dfa const & d) : d(d) {}

void state_machine::start(details::subjob & sj, int documentPosition) const {
	process(sj.construct_context(documentPosition), 0);
}

void state_machine::process(details::context c, int s) const {
	if (s == d.function.size() - 1) {
		accept(c);
	}
	for (auto const & kvp : d.function[s]) {
		recognizer const & transition = kvp.first;
		int const next_state = kvp.second;
		on(c, transition, next_state);
	}
}

//hook up an event handler
void state_machine::on(details::context c, recognizer const & r, int nextDfaState) const {
	c.owner().on(c, r, nextDfaState);
}

void state_machine::accept(details::context c) const {
	c.owner().add_result(c.current_document_position() - c.owner().document_position, c.result());
}





}
