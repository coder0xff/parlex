#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>

#include "recognizer.hpp"
#include "dfa.hpp"

namespace parlex {

//simulates a dfa
class state_machine : public recognizer {
public:
	state_machine(dfa const & d);
	virtual ~state_machine() = default;
	void start(safe_ptr<details::parse_context> c) const final;
private:
	dfa d;
	void process(safe_ptr<details::parse_context> c, int nextDfaState) const final;
};

}

#endif
