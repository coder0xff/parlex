#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>

namespace parlex {

class state_machine : public recognizer {
public:
	state_machine(nfa a);
};

typedef std::shared_ptr<state_machine> state_machine_sp;

}

#endif