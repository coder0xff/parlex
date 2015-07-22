#ifndef MATCH_HPP
#define MATCH_HPP

#include "match_class.hpp"

namespace parlex {
namespace details {

struct match {
	struct match_class match_class;
	int consumed_character_count;

	inline match(struct match_class const & matchCategory, int consumedCharacterCount) : match_class(matchCategory), consumed_character_count(consumedCharacterCount) {}

	inline bool operator <(match const & rhs) const {
		return consumed_character_count < rhs.consumed_character_count || 
			(consumed_character_count == rhs.consumed_character_count && match_class < rhs.match_class);
	}

	inline bool operator !=(match const & rhs) const {
		return *this < rhs || rhs < *this;
	}

	inline bool operator ==(match const & rhs) const {
		return !(*this != rhs);
	}
};

}
}

#endif