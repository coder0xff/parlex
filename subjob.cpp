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
		if (subscription.context.owner.completed) {
			continue;
		}
		while (subscription.next_index < matchToPermutations.size()) {
			auto match = matches[subscription.next_index];
			subscription.next_index++;			
			owner.owner.schedule([](){
				parse_context next = subscription.context;
				next.current_document_position += match.consumedCharacterCount;
				subscription.f
			}); //subscription.context, match);
		};
	}
}

void subjob::start() {
	process_state(state_machine->start_state, document_position, std::vector<match>());
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