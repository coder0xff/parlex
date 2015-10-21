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
	state_machine(std::string id, dfa const & d);
	virtual ~state_machine() = default;
	void start(details::subjob & sj, int documentPosition) const;
	std::string get_id() const final;
private:
	friend class parser;
	std::string id;
	dfa d;
	void process(details::context const & c, int dfaState) const;
	void on(details::context const & c, recognizer const & r, int nextDfaState) const;
	void accept(details::context const & c) const;
};

}

#endif
