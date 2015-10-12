#include "terminal.hpp"

#include "context.hpp"
#include "subjob.hpp"
#include "job.hpp"
#include "token.hpp"

namespace parlex {

void terminal::start(details::job const & j, details::token & t, int documentPosition) const {
	if (test(j.document, documentPosition)) {
		t.add_result(get_length(), std::vector<details::match>());
	}
}

}
