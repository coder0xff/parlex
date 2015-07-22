#ifndef ABSTRACT_SYNTAX_GRAPH_HPP
#define ABSTRACT_SYNTAX_GRAPH_HPP

#include <map>
#include <set>

#include "match_class.hpp"
#include "permutation.hpp"

namespace parlex {

struct abstract_syntax_graph {
	inline abstract_syntax_graph(details::match_class root) : root(root) {}
	std::map<details::match_class, std::set<permutation>> table;
	details::match_class root;
};

}

#endif