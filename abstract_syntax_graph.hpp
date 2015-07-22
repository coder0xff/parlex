#ifndef ABSTRACT_SYNTAX_GRAPH_HPP
#define ABSTRACT_SYNTAX_GRAPH_HPP

#include <map>
#include <set>

#include "match.hpp"
#include "permutation.hpp"

namespace parlex {

struct abstract_syntax_graph {
	inline abstract_syntax_graph(details::match root) : root(root) {}
	std::map<details::match, std::set<permutation>> table;
	details::match root;
};

}

#endif