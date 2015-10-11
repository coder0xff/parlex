#include "state_machine.hpp"
#include "parse_context.hpp"

namespace parlex {

state_machine::state_machine(dfa const & d) : d(d) {}

void state_machine::start(safe_ptr<details::parse_context> c) const {
	process(c, 0);
}

void state_machine::process(safe_ptr<details::parse_context> c, int s) const {
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
