#ifndef PARSE_CONTEXT_HPP
#define PARSE_CONTEXT_HPP

#include <vector>

#include "match_category.hpp"

namespace parlex {

class dfa;

namespace details {

class job;

struct parse_context {
	job * const owner;
	int const subjob_document_position;
	int current_document_position;
	std::vector<match_class> preceeding_match_classes;
	dfa const * const recognizer;

	inline parse_context(job * owner, int document_position, dfa const * recognizer) : owner(owner), subjob_document_position(document_position), recognizer(recognizer) {
		current_document_position = document_position;
	}
};

}
}

#endif