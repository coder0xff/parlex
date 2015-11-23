#ifndef RULE_HPP
#define RULE_HPP

namespace parlex {

class rule {
	recognizer r;
	std::vector<filter> filters;
};
}

#endif