#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

#include <map>
#include <string>

#include "dfa.hpp"

namespace parlex {

typedef std::map<std::string, recognizer> grammar;

}

#endif