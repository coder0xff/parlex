#ifndef SUBJOB_HPP
#define SUBJOB_HPP

#include <list>
#include <map>
#include <mutex>
#include <set>
#include <atomic>

#include "match.hpp"
#include "permutation.hpp"
#include "dfa.hpp"
#include "context.hpp"
#include "producer.hpp"

namespace parlex {

class state_machine;

namespace details {

class job;

class subjob : public producer {
public:
	state_machine const & machine;
	std::list<context> contexts;
	std::mutex mutex;

	subjob(job & owner, state_machine const & machine, int const documentPosition);
	subjob(subjob const & other) = delete;
	subjob(subjob&& move) = default;

	void start();
	context_ref step(context_ref const & prior, match const fromTransition);
	void on(context_ref const & c, recognizer const & r, int nextDfaState);
	void accept(context_ref const & c);
	context_ref construct_context(int documentPosition);
	//The parser invokes this method when none of this subjobs dependencies will produce further output
	void flush();
};

}
}

#endif
