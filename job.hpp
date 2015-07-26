#ifndef JOB_H
#define JOB_H

#include <string>

#include "recognizer.hpp"
#include "match_class.hpp"
#include "subjob.hpp"
#include "abstract_syntax_graph.hpp"

namespace parlex {

class parser;

namespace details {

//holds the state of the parser during a parse
//making it a type makes it easy for the parser to reset its state
class job {
public:
	std::u32string const document;
	recognizer const & main;
	std::map<match_class, subjob> subjobs;
	abstract_syntax_graph result;

	job(parser * owner, std::u32string const & document, recognizer const & main);
	void connect(subjob * dependent, match_class const & match_class, parse_context const & context);
	void start();
private:
	friend details::subjob;
	parser * owner;
};

}
}

#endif