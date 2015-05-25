#ifndef ABSTRACT_SYNTAX_GRAPH_HPP
#define ABSTRACT_SYNTAX_GRAPH_HPP

namespace parlex {

struct abstract_syntax_graph {
	std::map<match_class, std::set<match>> table;
	match_class root;
};

}

#endif