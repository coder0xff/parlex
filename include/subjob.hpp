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
#include "parse_context.hpp"

namespace parlex {
namespace details {

class job;

class subjob {
public:
	struct subscription {
		int next_index;
		safe_ptr<parse_context> const context;
		int next_dfa_state;
		inline subscription(safe_ptr<parse_context> const context, int const nextDfaState) : next_index(0), context(context), next_dfa_state(nextDfaState) {}
	};

	job & owner;
	recognizer const & r;
	int const document_position;
	std::atomic<bool> completed;
	std::list<subscription> subscriptions;
	std::vector<match> matches;
	std::vector<safe_ptr<parse_context>> contexts;
	std::map<match, std::set<permutation>> match_to_permutations;
	std::recursive_mutex mutex;

	subjob(job & owner, recognizer const & r, int const documentPosition);
	subjob(subjob const & other) = delete;
	void start();
	safe_ptr<parse_context> step(safe_ptr<parse_context const> const prior, match const fromTransition);

	void on_recognizer_accepted(int const charCount, std::vector<match> const & children);
	void do_events();

	void add_subscription(safe_ptr<parse_context> const context, int const nextDfaState);
	void on_dead_lock();
	void on_completed();
};

}
}

#endif
