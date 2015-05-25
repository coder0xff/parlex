#ifndef RECOGNIZER_HPP
#define RECOGNIZER_HPP

#include <memory>

namespace parlex {

//inherited by terminal and dfa
class recognizer {
public:
	virtual ~recognizer() = default;
};

}

#endif