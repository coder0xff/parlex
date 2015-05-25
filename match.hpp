#ifndef MATCH_HPP
#define MATCH_HPP

#include "match_class.hpp"

namespace parlex {

struct match {
	details::match_class match_class;
	recognizer * recognizer;
	std::vector<details::match_class> children;
};

}

#endif