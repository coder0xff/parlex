#ifndef GRAMMAR_HPP
#define GRAMMAR_HPP

namespace parlex {

template<TStateMachine>
typedef std::dictionary<std::string, TStateMachine> grammar;

}

#endif