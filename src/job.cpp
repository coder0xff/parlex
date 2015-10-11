#include "job.hpp"
#include "terminal.hpp"
#include "parse_context.hpp"
#include "parser.hpp"

namespace parlex {
namespace details {

job::job(parser & owner, std::u32string const & document, recognizer const & main) :
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

void job::connect(match_class const & matchClass, safe_ptr<parse_context> context, int nextDfaState) {
	subjob * sj = nullptr;
	{
		std::unique_lock<std::mutex> lock(subjobs_mutex);
		// get or insert the subjob for matchClass
		auto pair = subjobs.emplace(
			std::piecewise_construct,
			std::forward_as_tuple(matchClass),
			std::forward_as_tuple(*this, matchClass.r, matchClass.document_position));
		// start it if inserted
		if (pair.second) {
			pair.first->second.start();
		}
		sj = &pair.first->second;
	}
	sj->add_subscription(context, nextDfaState);
}

}
}
