#include "state_machine.hpp"

namespace parlex {

state_machine::state_machine(dfa const & d) : d(d) {}

void state_machine::start(details::parse_context const & c) const {
	process(c, 0);
}

void state_machine::process(details::parse_context const & c, int s) const {
	if (s == d.function.size() - 1) {
		accept(c);
	}
	for (auto const & kvp : d.function[s]) {
		recognizer const & transition = kvp.first;
		int const next_state = kvp.second;
		on(c, transition, next_state);
	}
}





}
