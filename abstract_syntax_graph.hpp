#ifndef ABSTRACT_SYNTAX_GRAPH_HPP
#define ABSTRACT_SYNTAX_GRAPH_HPP

#include <map>
#include <set>

#include "match_class.hpp"
#include "match.hpp"

namespace parlex {

struct abstract_syntax_graph {
	inline abstract_syntax_graph(details::match_class root) : root(root) {}
	std::map<details::match_class, std::set<match>> table;
	details::match_class root;
};

}

#endif