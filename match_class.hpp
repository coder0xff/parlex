#ifndef MATCH_CLASS_H
#define MATCH_CLASS_H

#include "match_category.hpp"

namespace parlex {
namespace details {

struct match_class {
	struct match_category match_category;
	int consumed_character_count;

	inline match_class(struct match_category const & matchCategory, int consumedCharacterCount) : match_category(matchCategory), consumed_character_count(consumedCharacterCount) {}

	inline bool operator <(match_class const & rhs) const {
		return consumed_character_count < rhs.consumed_character_count || 
			(consumed_character_count == rhs.consumed_character_count && match_category < rhs.match_category);
	}

	inline bool operator !=(match_class const & rhs) const {
		return *this < rhs || rhs < *this;
	}

	inline bool operator ==(match_class const & rhs) const {
		return !(*this != rhs);
	}
};

}
}

#endif