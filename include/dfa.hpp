#ifndef DFA_HPP
#define DFA_HPP

#include <vector>
#include <map>
#include <algorithm>
#include <functional>

#include "recognizer.hpp"

namespace parlex {

struct dfa {
public:
	//State 0 is the start state
	//States from N-a to N-1 are the accept states, where N is the number of states and a is the number of accepts states
	std::vector<std::map<std::reference_wrapper<recognizer const>, int, details::recognizer_reference_comparer>> function;
	int accept_state_count; //a must be greater than 0

	void add_transition(int fromState, recognizer const & recognizer, int toState);
};

}

#endif
