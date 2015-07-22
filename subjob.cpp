#include "subjob.hpp"

#include <string>

#include "parse_context.hpp"
#include "job.hpp"
#include "recognizer.hpp"

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
		while (subscription.next_index < classes.size()) {
			auto match = classes[subscription.next_index];
			subscription.next_index++;			
			owner->schedule(subscription.context, match);
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
		accept(current_document_position - document_position);
	}
	for (auto const & kvp : state_machine->function[state]) {
		recognizer const * transition = kvp.first;
		int next_state = kvp.second;
		parse_context context(this, current_document_position, next_state);
		match_class category(transition, current_document_position);
		owner->connect(this, category, context);
	}
}

}
}