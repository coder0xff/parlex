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
	std::mutex subjobs_mutex;
	abstract_syntax_graph result;

	job(parser & owner, std::u32string const & document, recognizer const & main);
	void connect(match_class const & matchClass, parse_context const & context, int nextState);
	void start();
private:
	friend details::subjob;
	parser & owner;
};

}
}

#endif
