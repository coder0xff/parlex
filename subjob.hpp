#ifndef SUBPARSE_HPP
#define SUBPARSE_HPP

#include <list>
#include <vector>
#include <map>
#include <mutex>

#include "match_class.hpp"
#include "match.hpp"
#include "dfa.hpp"
#include "parse_context.hpp"

namespace parlex {
namespace details {

class job;

class subjob {
public:
	subjob(job * owner, dfa const * recognizer, int documentPosition);
	subjob(subjob const & other) = delete;

	void receive_subscription(parse_context const & context, subjob * subscriber);

	struct subscription {
		int next_index;
		parse_context const context;
		subjob * const dependent;
		inline subscription(parse_context const & context, subjob * dependent) : next_index(0), context(context), dependent(dependent) {}
	};

	job * const owner;
	dfa const * const recognizer;
	int document_position;
	bool completed;
	std::list<subscription> subscriptions;
	std::vector<match_class> classes;
	std::map<match_class, match> matches;
	std::mutex mutex;

	void start(parse_context const & context);
	void process_state(int state, parse_context const & context);
	void accept(int consumedCharacterCount) const;
	void do_events();
	void step(parse_context const & context, match_class const & match_class);
};

}
}

#endif