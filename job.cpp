#include "job.hpp"
#include "terminal.hpp"
#include "parse_context.hpp"
#include "parser.hpp"

namespace parlex {
namespace details {

job::job(parser * owner, std::u32string const & document, recognizer const & main) :
		owner(owner),
		document(document),
		main(main),
		result(match(match_class(main, 0), document.size()))
	{
		std::unique_lock<std::mutex> lock;
		auto pair = subjobs.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(match_class(main, 0)),
			std::forward_as_tuple(*this, main, 0));
		pair.first->second.start();
	}

void job::connect(subjob * dependent, match_class const & matchClass, parse_context const & context) {
	std::unique_lock<std::mutex> lock;
	auto pair = subjobs.emplace(
		std::piecewise_construct,
		std::forward_as_tuple(matchClass),
		std::forward_as_tuple(*this, matchClass.r, matchClass.document_position));
	if (pair.second) {
		pair.first->second.start();
	}
	pair.first->second.add_subscription(context);
}

}
}