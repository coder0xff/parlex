#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>

#include "recognizer.hpp"
#include "dfa.hpp"
#include "context.hpp"

namespace parlex {

class parser;

//simulates a dfa
class state_machine : public recognizer {
public:
	state_machine(dfa const & d);
	virtual ~state_machine() = default;
	void start(details::subjob & sj, int documentPosition) const;
private:
	friend class parser;
	dfa d;
	void process(details::context c, int dfaState) const;
	void on(details::context c, recognizer const & r, int nextDfaState) const;
	void accept(details::context c) const;
};

}

#endif
