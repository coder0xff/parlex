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
		parse_context const context;
		inline subscription(parse_context const & context) : next_index(0), context(context) {}
	};

	job const & owner;
	recognizer const & r;
	int document_position;
	std::atomic<bool> completed;
	std::list<subscription> subscriptions;
	std::vector<match> matches;
	std::map<match, std::set<permutation>> matchToPermutations;
	std::mutex mutex;

	subjob(job & owner, recognizer const & r, int documentPosition);
	subjob(subjob const & other) = delete;
	void start();
	void on_recognizer_accepted(int consumedCharacterCount, std::vector<match> const & children);
	void do_events();

	void add_subscription(parse_context const & context);
	void on_dead_lock();
	void on_completed();
};

}
}

#endif