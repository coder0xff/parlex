#include "subjob.hpp"

#include <string>

#include "parse_context.hpp"
#include "job.hpp"
#include "recognizer.hpp"
#include "parser.hpp"

namespace parlex {
namespace details {

subjob::subjob(
	job * owner,
	dfa const * stateMachine,
	int documentPosition
):
	owner(owner),
	state_machine(stateMachine),
	completed(0),
	document_position(documentPosition)
{ }

void subjob::add_subscription(parse_context const & context) {
	{
		std::unique_lock<std::mutex> lock(mutex);
		subscriptions.emplace_back(context);
	}  //release the lock
	do_events();
}

void subjob::do_events() {
	std::unique_lock<std::mutex> lock(mutex);
	for (auto & subscription : subscriptions) {
		while (subscription.next_index < matchToPermutations.size()) {
			auto match = matches[subscription.next_index];
			subscription.next_index++;			
			owner->owner->schedule(subscription.context, match);
		};
	}
}

void subjob::start() {
	process_state(state_machine->start_state, document_position, std::vector<match>());
}

void subjob::process_state(
		int state,
		int current_document_position,
		std::vector<match> const & preceding_permutations) {

	if (state == state_machine->accept_state) {
		accept(current_document_position - document_position, std::vector<match>());
	}
	for (auto const & kvp : state_machine->function[state]) {
		recognizer const * transition = kvp.first;
		int next_state = kvp.second;
		parse_context context(this, current_document_position, next_state);
		match_class matchClass(transition, current_document_position);
		owner->connect(this, matchClass, context);
	}
}

void subjob::accept(int consumedCharacterCount, std::vector<match> const & children) {
	bool newMatch = false;
	{
		std::unique_lock<std::mutex> lock(mutex);
		match m(match_class(state_machine, document_position), consumedCharacterCount);
		if (!matchToPermutations.count(m)) {
			matchToPermutations[m] = std::set<permutation>();
			matches.push_back(m);
			newMatch = true;			
		}
		matchToPermutations[m].insert(children);
	}
	if (newMatch) {
		do_events();
	}
}


}
}