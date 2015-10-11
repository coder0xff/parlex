#ifndef PARSE_CONTEXT_HPP
#define PARSE_CONTEXT_HPP

#include <memory>
#include <vector>

#include "match.hpp"
#include "match_class.hpp"
#include "safe_ptr.hpp"

namespace parlex {
namespace details {

class subjob;

struct parse_context {
	parse_context(subjob & owner, safe_ptr<parse_context const> const prior, int const document_position, match const * from_transition);
	parse_context(parse_context const & other) = delete;
	subjob & owner;
	safe_ptr<parse_context const> const prior;
	int const current_document_position;
	//unique_ptr is used to simulate an "optional"
	std::unique_ptr<match const> const from_transition;

	std::vector<match> result() const;
};

}
}

#endif
