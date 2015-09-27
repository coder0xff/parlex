#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>

#include "recognizer.hpp"
#include "dfa.hpp"

namespace parlex {

//simulates a dfa
class state_machine : public recognizer {
public:
	state_machine(dfa d);
	virtual ~state_machine() = default;
	void start(details::parse_context const & c) const final;
private:
	dfa d;
	void process(details::parse_context const & c, int nextDfaState) const final;
};

}

#endif
