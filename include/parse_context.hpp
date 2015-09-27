#ifndef PARSE_CONTEXT_HPP
#define PARSE_CONTEXT_HPP

#include <vector>

#include "match.hpp"
#include "match_class.hpp"

namespace parlex {

class dfa;

namespace details {

class subjob;

struct parse_context {
	subjob & owner;
	int current_document_position;
	std::vector<match> permutation_builder;

	inline parse_context(subjob & owner, int document_position) :
			owner(owner),
			current_document_position(document_position) {
	}

	inline parse_context step(match match) const {
		parse_context result = *this;
		result.current_document_position += match.consumed_character_count;
		result.permutation_builder.push_back(match);
		return result;
	}
};

}
}

#endif