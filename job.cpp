#include "job.hpp"
#include "terminal.hpp"
#include "parse_context.hpp"

namespace parlex {
namespace details {

void job::connect_dependent(subjob * dependent, int nextState, parse_context const & context, match_category const & match_category) {
	auto as_terminal = dynamic_cast<terminal const *>(match_category.recognizer);
	if (as_terminal) {
		if (as_terminal->test(document, match_category.document_position)) {
			auto new_parse_context = context;
			new_parse_context.current_document_position += as_terminal->get_length();
			dependent->process_state(nextState, new_parse_context);
		}
	} else {
		auto recognizer = static_cast<dfa const *>(match_category.recognizer);
		std::unique_lock<std::mutex> lock;
		auto pair = subjobs.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(match_category),
			std::forward_as_tuple(this, recognizer, match_category.document_position));
		if (pair.second) {
			parse_context context(this, match_category.document_position, recognizer);
			pair.first->second.start(context);
		}
		pair.first->second.receive_subscription(context, dependent);
	}
}

}
}