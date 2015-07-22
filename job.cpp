#include "job.hpp"
#include "terminal.hpp"
#include "parse_context.hpp"
#include "parser.hpp"

namespace parlex {
namespace details {

job::job(parser * owner, std::u32string const & document, dfa const & main) :
		owner(owner),
		document(document),
		main(main)
	{
		std::unique_lock<std::mutex> lock;
		auto pair = subjobs.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(match_class(&main, 0)),
			std::forward_as_tuple(this, &main, 0));
		pair.first->second.start();
	}

void job::connect(subjob * dependent, match_class const & matchCategory, parse_context const & context) {
	auto as_terminal = dynamic_cast<terminal const *>(matchCategory.recognizer);
	if (as_terminal) {
		if (as_terminal->test(document, matchCategory.document_position)) {
			match matchClass(matchCategory, as_terminal->get_length());
			schedule(context, matchClass);
		}
	} else {
		auto recognizer = static_cast<dfa const *>(matchCategory.recognizer);
		std::unique_lock<std::mutex> lock;
		auto pair = subjobs.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(matchCategory),
			std::forward_as_tuple(this, recognizer, matchCategory.document_position));
		if (pair.second) {
			pair.first->second.start();
		}
		pair.first->second.add_subscription(context);
	}
}

}
}