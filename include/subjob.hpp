#ifndef SUBJOB_HPP
#define SUBJOB_HPP

#include <list>
#include <vector>
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
	std::vector<context> contexts;
	std::recursive_mutex mutex;

	subjob(job & owner, state_machine const & machine, int const documentPosition);
	subjob(subjob const & other) = delete;
	subjob(subjob&& move) = default;

	void start();
	context step(context const prior, match const fromTransition);
	void on(context const c, recognizer const & r, int nextDfaState);
	context construct_context(int documentPosition);
	void handle_halt();
};

}
}

#endif
