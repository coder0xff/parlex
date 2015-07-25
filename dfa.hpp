#ifndef DFA_HPP
#define DFA_HPP

#include <vector>
#include <map>

#include "recognizer.hpp"

namespace parlex {

class dfa : public recognizer {
public:
	inline dfa() : start_state(-1), accept_state(-1) {}
	virtual ~dfa() = default;
	std::vector<std::map<recognizer const *, int>> function;
	int start_state;
	int accept_state;
};

}

#endif