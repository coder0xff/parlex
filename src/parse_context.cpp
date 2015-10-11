/*
 * parse_context.cpp
 *
 *  Created on: Sep 27, 2015
 *      Author: brent
 */

#include <cassert>
#include "parse_context.hpp"
#include "subjob.hpp"

namespace parlex {
namespace details {

parse_context::parse_context(subjob & owner, safe_ptr<parse_context const> const prior, int const document_position, match const * from_transition) :
			owner(owner),
			prior(prior),
			current_document_position(document_position),
			from_transition(from_transition ? new match(*from_transition) : nullptr)
	{
		assert(&owner);
		assert((bool)prior == (bool)from_transition);
	}

	std::vector<match> parse_context::result() const {
		if (prior) {
			assert(from_transition);
			auto result = prior->result();
			result.push_back(*from_transition);
			return result;
		} else {
			return std::vector<match>();
		}
	}

}}
