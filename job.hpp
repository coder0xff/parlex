#ifndef JOB_H
#define JOB_H

#include <string>

#include "dfa.hpp"
#include "subjob.hpp"

namespace parlex {
namespace details {

class job {
public:
	std::u32string const document;
	dfa const recognizer;
	void connect_dependent(subjob * dependent, int nextState, parse_context const & context, match_category const & match_category);
	void schedule(std::function<void ()> work);
private:
	std::map<match_category, subjob> subjobs;
	std::mutex mutex;
};

}
}

#endif