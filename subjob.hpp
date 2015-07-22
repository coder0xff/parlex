#ifndef SUBJOB_HPP
#define SUBJOB_HPP

#include <list>
#include <vector>
#include <map>
#include <mutex>
#include <set>

#include "match_class.hpp"
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

	job * const owner;
	dfa const * const state_machine;
	int document_position;
	bool completed;
	std::list<subscription> subscriptions;
	std::vector<match_class> classes;
	std::map<match_class, std::set<permutation>> matches;
	std::mutex mutex;

	subjob(job * owner, dfa const * recognizer, int documentPosition);
	subjob(subjob const & other) = delete;
	void start();
	void process_state(int state, int current_document_position, std::vector<match_class> const & preceding_matches);
	void accept(int consumedCharacterCount) const;
	void do_events();
	void step(parse_context const & context, match_class const & match_class);

	void add_subscription(parse_context const & context);
};

}
}

#endif