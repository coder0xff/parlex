#ifndef JOB_H
#define JOB_H

#include <string>

#include "dfa.hpp"
#include "subjob.hpp"

namespace parlex {

class parser;

namespace details {

//holds the state of the parser during a parse
//making it a type makes it easy for the parser to reset its state
class job {
public:
	std::u32string const document;
	dfa const main;
	std::map<match_class, subjob> subjobs;

	job(parser * owner, std::u32string const & document, dfa const & main);
	void connect(subjob * dependent, match_class const & match_class, parse_context const & context);
	void schedule(parse_context const & context, match const & match);
	void start();

private:
	parser * owner;
};

}
}

#endif