#include "dfa.hpp"

namespace parlex {

void dfa::add_transition(int fromState, recognizer const & recognizer, int toState) {
	while (function.size() <= std::max(fromState, toState)) {
		function.emplace_back();
	}
	if (!function[fromState].emplace(
			std::piecewise_construct,
			std::forward_as_tuple(recognizer),
			std::forward_as_tuple(toState)).second) {
		throw "transition already specified";
	}
}

}
