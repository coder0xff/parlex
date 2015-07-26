#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>

namespace parlex {

//simulates a dfa
class state_machine : public recognizer {
public:	
	state_machine(dfa d);
	virtual ~state_machine() = default;
	void start(parse_context const & c) const final;
	inline void halt(parse_context const & c) const final { recognizer::halt(); }
private:
	dfa d;

	void process_state(details::parse_context const & c, int s) const;
};

}

#endif