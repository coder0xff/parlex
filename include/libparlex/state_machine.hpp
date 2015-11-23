#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include <memory>

#include "recognizer.hpp"
#include "dfa.hpp"
#include "context.hpp"

namespace parlex {

class parser;

//simulates a dfa
//State 0 is the start state
//States from N-a to N-1 are the accept states, where N is states.size() and a is accept_state_count
class state_machine : public recognizer {
public:
	state_matchine(std::string id, int acceptStateCount, std::vector<std::reference_wrapper<filter const>> filters);
	virtual ~state_machine() = default;
	void start(details::subjob & sj, int documentPosition) const;

	void add_transition(int fromState, recognizer const & recognizer, int toState);
private:
	friend class parser;

	std::string const id;
	std::vector<std::reference_wrapper<filter const>> const filters;
	int const accept_state_count; //must be greater than 0
	std::vector<std::map<std::reference_wrapper<recognizer const>, int, details::recognizer_reference_comparer>> states;
	void on(details::context_ref const & c, recognizer const & r, int nextDfaState) const;
	void process(details::context_ref const & c, int dfaState) const;
	void accept(details::context_ref const & c) const;
};

}

#endif
