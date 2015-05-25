#include "subjob.hpp"

#include <string>

#include "parse_context.hpp"
#include "job.hpp"

namespace parlex {
namespace details {

subjob::subjob(
	job * owner,
	dfa const * recognizer,
	int documentPosition
):
	owner(owner),
	recognizer(recognizer),
	completed(0),
	document_position(documentPosition)
{ }

void subjob::receive_subscription(parse_context const & context, subjob * dependent) {
	{
		std::unique_lock<std::mutex> lock(mutex);
		subscriptions.emplace_back(context, dependent);
	}  //release the lock
	do_events();
}

void subjob::do_events() {
	std::unique_lock<std::mutex> lock(mutex);
	for (auto & subscription : subscriptions) {
		while (subscription.next_index < classes.size()) {
			auto dependent = subscription.dependent;
			auto parse_context = subscription.context;
			auto match_class = classes[subscription.next_index];
			subscription.next_index++;			
			owner->schedule([=]() {
				dependent->step(parse_context, match_class);
			});
		}
	}
}

void subjob::start(parse_context const & context) {
	process_state(recognizer->start_state, context);
}

void subjob::process_state(int state, parse_context const & context) {
	if (state == context.recognizer->accept_state) {
		accept(context.current_document_position - context.subjob_document_position);
	}
	for (auto const & kvp : context.recognizer->function[state]) {		
		match_category category;
		category.recognizer = kvp.first;
		category.document_position = context.current_document_position;
		owner->connect_dependent(this, kvp.second, context, category);
	}
}

}
}