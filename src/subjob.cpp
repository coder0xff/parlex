#include "subjob.hpp"

#include <string>

#include "parse_context.hpp"
#include "job.hpp"
#include "recognizer.hpp"
#include "parser.hpp"

namespace parlex {
namespace details {

subjob::subjob(
	job & owner,
	recognizer const & r,
	int documentPosition
):
	owner(owner),
	r(r),
	completed(0),
	document_position(documentPosition)
{ }

void subjob::add_subscription(safe_ptr<parse_context> context, int nextDfaState) {
	{
		std::unique_lock<std::recursive_mutex> lock(mutex);
		subscriptions.emplace_back(context, nextDfaState);
	}  //release the lock
	do_events();
}

void subjob::do_events() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	for (auto & subscription : subscriptions) {
		if (subscription.context->owner.completed) {
			continue;
		}
		while (subscription.next_index < match_to_permutations.size()) {
			auto match = matches[subscription.next_index];
			subscription.next_index++;
			safe_ptr<parse_context> next = step(subscription.context, match);
			owner.owner.schedule(next, subscription.next_dfa_state);
		};
	}
}

void subjob::start() {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	contexts.emplace_back(safe_ptr<parse_context>::construct(*this, safe_ptr<parse_context>(), document_position, nullptr));
	r.start(contexts.back());
}

safe_ptr<parse_context> subjob::step(safe_ptr<const parse_context> prior, match fromTransition) {
	std::unique_lock<std::recursive_mutex> lock(mutex);
	contexts.emplace_back(safe_ptr<parse_context>::construct(*this, prior, prior->current_document_position + fromTransition.consumed_character_count, &fromTransition));
	auto result = contexts.back();
	r.start(result);
	return result;
}

void subjob::on_recognizer_accepted(int consumedCharacterCount, std::vector<match> const & children) {
	bool newMatch = false;
	{
		std::unique_lock<std::recursive_mutex> lock(mutex);
		match m(match_class(r, document_position), consumedCharacterCount);
		if (!match_to_permutations.count(m)) {
			match_to_permutations[m] = std::set<permutation>();
			matches.push_back(m);
			newMatch = true;
		}
		match_to_permutations[m].insert(children);
	}
	if (newMatch) {
		do_events();
	}
}


}
}
