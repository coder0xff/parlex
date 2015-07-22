#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "recognizer.hpp"

namespace parlex {

class terminal : public recognizer {
public:
	virtual ~terminal() = default;
	virtual bool test(std::u32string document, int documentPosition) const = 0;
	virtual int get_length() const = 0;
};

}

#endif