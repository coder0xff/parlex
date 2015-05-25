#ifndef MATCH_CATEGORY_H
#define MATCH_CATEGORY_H

#include "match_category.hpp"

namespace parlex {
namespace details {

struct match_class {
	match_category match_category;
	int consumed_character_count;
	inline bool operator <(match_class const & rhs) const {
		return consumed_character_count < rhs.consumed_character_count || 
			(consumed_character_count == rhs.consumed_character_count && match_category < rhs.match_category);
	}
};

}
}

#endif