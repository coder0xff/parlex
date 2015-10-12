/*
 * context.cpp
 *
 *  Created on: Sep 27, 2015
 *      Author: brent
 */

#include <cassert>
#include "context.hpp"
#include "subjob.hpp"

namespace parlex {
namespace details {

context_storage::context_storage(subjob & owner, context const prior, int const document_position, match const * from_transition) :
			owner(owner),
			prior(prior),
			current_document_position(document_position),
			from_transition(from_transition ? new match(*from_transition) : nullptr)
	{
		assert(&owner);
		assert(!prior.is_null() == (bool)from_transition);
	}

context::context() : is_owner(false), rc(nullptr) { }

context::context(subjob & owner, context const prior, int const document_position, match const * from_transition) :
 is_owner(true), 
 rc(new context_ref_counter(new context_storage(owner, prior, document_position, from_transition)))
{ }

context::context(context const & other) : is_owner(false), rc(other.rc) {
	if (rc) {
		rc->inc();
	}
}

context::context(context&& move) : is_owner(false), rc(nullptr) {
	std::swap(is_owner, move.is_owner);
	std::swap(rc, move.rc);
}

context::~context() {
	if (rc) {
		if (is_owner) {
			context_storage* temp = rc->underlying.exchange(nullptr);
			delete temp;
		}
		rc->dec();
	}
}

context & context::operator =(context const & other) {
	context temp(other);
	std::swap(is_owner, temp.is_owner);
	std::swap(rc, temp.rc);
	return *this;
}

std::vector<match> context::result() const {
	context_storage* temp = rc->underlying;
	if (temp->prior.is_null()) {
		return std::vector<match>();
	} else {
		assert(temp->from_transition);
		auto result = temp->prior.result();
		result.push_back(*temp->from_transition);
		return result;
	}
}

bool context::is_null() const {
	if (rc == nullptr) {
		return true;
	} else {
		assert(rc->underlying);
		return false;
	}
}

subjob & context::owner() const {
	assert(rc);
	context_storage* temp = rc->underlying;
	assert(temp);
	return temp->owner;
}

context context::prior() const {
	assert(rc);
	context_storage* temp = rc->underlying;
	assert(temp);
	return temp->prior;
}

int context::current_document_position() const {
	assert(rc);
	context_storage* temp = rc->underlying;
	assert(temp);
	return temp->current_document_position;
}

std::unique_ptr<match> context::from_transition() const {
	assert(rc);
	context_storage* temp = rc->underlying;
	assert(temp);
	if (temp->from_transition) {
		return std::unique_ptr<match>(new match(*temp->from_transition));
	} else {
		return std::unique_ptr<match>();
	}
}

}}
