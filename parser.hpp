#ifndef PARSER_HPP
#define PARSER_HPP

#include "abstract_syntax_graph.hpp"

namespace parlex {

class parser {
public:
	parser(int thread_count = std::thread::max_concurrency());
	abstract_syntax_graph parse(grammar g, std::u32string document);
private:	
};

}

#endif