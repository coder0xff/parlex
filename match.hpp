#ifndef MATCH_HPP
#define MATCH_HPP

#include <vector>

#include "match_class.hpp"

namespace parlex {

typedef std::vector<details::match_class> match;

/*struct match {
	int length;
	std::vector<details::match_class> children;

	inline match(int length, std::vector<details::match_class> children) : length(length), children(children) {}
};*/

}

#endif