#ifndef PRODUCER_HPP
#define PRODUCER_HPP

#include <list>
#include <map>
#include <vector>
#include <set>
#include <mutex>

#include "context.hpp"
#include "permutation.hpp"

namespace parlex {

class parser;

namespace details {

class job;

class producer {
	struct subscription {
		int next_index;
		context_ref const c;
		int next_dfa_state;
		inline subscription(context_ref const & c, int const nextDfaState) : next_index(0), c(c), next_dfa_state(nextDfaState) {}
	};

	void do_events();

public:
	job & owner;
	recognizer const & r;
	int const document_position;
private:
	std::atomic<bool> completed;
	std::list<subscription> subscriptions;
	std::vector<match> matches;
	std::map<match, std::set<permutation>> match_to_permutations;
	std::mutex mutex;
	friend class parlex::parser;
protected:
	producer(job & owner, recognizer const & r, int const documentPosition);

public:
	void enqueue_permutation(int consumedCharacterCount, permutation const & p);
	void add_subscription(context_ref const & c, int const nextDfaState);
};

}
}

#endif //PRODUCER_HPP