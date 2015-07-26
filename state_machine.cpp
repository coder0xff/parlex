#include "state_machine.hpp"

namespace parlex {

state_machine::state_machine(dfa d) : d(d) {}

void state_machine::start(parse_context const & c) {
	process_state(c, d.start_state);
}

void state_machine::process_state(parse_context const & c, int s) const {
	if (s == d.accept_state) {
		accept(c);
	}
	for (auto const & kvp : state_machine->function[state]) {
		recognizer const * const transition = kvp.first;
		int const next_state = kvp.second;
		on(c, transition, [this](parse_context const &c) { process_state(c, next_state); });
	}
}





}