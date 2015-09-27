#ifndef DFA_HPP
#define DFA_HPP

#include <vector>
#include <map>

#include "recognizer.hpp"

namespace parlex {

class dfa {
public:
	inline dfa() {}
	virtual ~dfa() = default;
	//state 0 is the start state
	//state N-1 is the accept state, where N is the number of states
	std::vector<std::map<std::reference_wrapper<recognizer const>, int, details::recognizer_reference_comparer>> function;
};

}

#endif
