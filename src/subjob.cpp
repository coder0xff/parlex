#include <iostream>
#include <string>

#include "subjob.hpp"
#include "context.hpp"
#include "job.hpp"
#include "recognizer.hpp"
#include "parser.hpp"
#include "state_machine.hpp"

namespace parlex {
namespace details {

subjob::subjob(
	job & owner,
	state_machine const & machine,
	int documentPosition
):
	producer(owner, machine, documentPosition),
	machine(machine)
{ 
	std::cout << "started a subjob at " << documentPosition << " using " << machine.get_id() << std::endl;
}

void subjob::start() {
	{
		std::unique_lock<std::mutex> lock(mutex);
		contexts.emplace_back(*this, context(), document_position, nullptr);
	}
	machine.start(*this, document_position);
}

context subjob::construct_context(int documentPosition) {
	std::unique_lock<std::mutex> lock(mutex);
	contexts.emplace_back(*this, context(), document_position, nullptr);
	return contexts.back();
}

context subjob::step(context const & prior, match fromTransition) {
	std::unique_lock<std::mutex> lock(mutex);
	contexts.emplace_back(*this, prior, prior.current_document_position() + fromTransition.consumed_character_count, &fromTransition);
	auto result = contexts.back();
	return result;
}

void subjob::on(context const & c, recognizer const & r, int nextDfaState) {
	owner.connect(details::match_class(r, c.current_document_position()), c, nextDfaState);
}

}
}
