#ifndef PARSE_CONTEXT_HPP
#define PARSE_CONTEXT_HPP

#include <vector>

#include "match_class.hpp"

namespace parlex {

class dfa;

namespace details {

class subjob;

struct parse_context {
	subjob * owner;
	int current_document_position;
	std::vector<match> preceeding_match_classes;
	int dfa_state;

	inline parse_context(subjob * owner, int document_position, int dfa_state) :
			owner(owner),
			current_document_position(document_position),
			dfa_state(dfa_state) {
	}

	inline parse_context step(match matchClass, int dfa_state) {
		parse_context result = *this;
		result.current_document_position += matchClass.consumed_character_count;
		result.preceeding_match_classes.push_back(matchClass);
		result.dfa_state = dfa_state;
		return result;
	}
};

}
}

#endif