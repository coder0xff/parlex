/*
 * context.cpp
 *
 *  Created on: Sep 27, 2015
 *      Author: brent
 */

#include <cassert>
#include <iostream>

#include "context.hpp"
#include "subjob.hpp"

std::atomic<int> context_counter(0);
std::atomic<int> storage_counter(0);

namespace parlex {
namespace details {

struct context_storage {
	context_storage(subjob & owner, context const & prior, int const document_position, match const * from_transition);
	context_storage(context const & other) = delete;
	subjob & owner;
	context const prior;
	int const current_document_position;
	//unique_ptr is used to simulate an "optional"
	std::unique_ptr<match const> const from_transition;	
};

struct context_ref_counter {
	std::atomic<context_storage *> underlying;
	std::atomic<int> counter;
	int const id;

	context_ref_counter(context_storage * underlying);
	void inc();
	void dec();
};

context_storage::context_storage(subjob & owner, context const & prior, int const document_position, match const * from_transition) :
			owner(owner),
			prior(prior),
			current_document_position(document_position),
			from_transition(from_transition ? new match(*from_transition) : nullptr)
	{
		assert(&owner);
		assert(!prior.is_null() == (bool)from_transition);
	}

context::context() : is_owner(false), rc(nullptr), id(++context_counter) {
	std::cout << "empty constructing context " << id << std::endl;
}

context::context(subjob & owner, context const & prior, int const document_position, match const * from_transition) :
 is_owner(true), 
 rc(new context_ref_counter(new context_storage(owner, prior, document_position, from_transition))),
 id (++context_counter)
{
	context_storage* temp = rc->underlying;
	std::cout << "constructed context " << id << " owning ref " << rc->id << std::endl;
}

context::context(context const & other) : is_owner(false), rc(other.rc), id(++context_counter) {
	if (rc) {
		rc->inc();
		std::cout << "copy constructed context " << id << " from context " << other.id << " ref " << rc->id << std::endl;
	} else {
		std::cout << "copy constructed context " << id << " from context " << other.id << " null" << std::endl;
	}
}

context::context(context&& move) : is_owner(false), rc(nullptr), id(++context_counter) {
	std::swap(is_owner, move.is_owner);
	if (move.rc) {
		std::swap(rc, move.rc);
		std::cout << "move constructed context " << id << " from context " << move.id << " ref " << rc->id << std::endl;
	} else {
		std::cout << "WARNING: move constructed context " << id << " from context " << move.id << " null" << std::endl;
	}
}

context::~context() {
	if (rc) {		
		if (is_owner) {
			int rcId = rc->id;			
			context_storage* temp = rc->underlying.exchange(nullptr);
			assert(temp);
			delete temp;
			rc->dec();
			std::cout << "destructed context " << id << " owning " << rcId << std::endl;
			return;
		}
		rc->dec();
	}
	std::cout << "destructed context " << id << std::endl;
}

context & context::operator =(context const & other) {
	context temp(other);
	std::swap(is_owner, temp.is_owner);
	std::swap(rc, temp.rc);
	return *this;
}

std::vector<match> context::result() const {
	assert(rc);
	context_storage* temp = rc->underlying;
	if (temp->prior.is_null()) {
		return std::vector<match>();
	} else {
		if (!temp->from_transition) {
			std::cout << "ERROR: access to stale context id: " << id << ", context_storage id: " << rc->id;
			throw;
		}
		auto result = temp->prior.result();
		result.push_back(*temp->from_transition);
		return result;
	}
}

bool context::is_null() const {
	if (rc == nullptr) {
		return true;
	} else {
		if (!rc->underlying) {
			std::cout << "ERROR: access to stale context id: " << id << ", context_storage id: " << rc->id;
			throw;
		}
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

context_ref_counter::context_ref_counter(context_storage * underlying) : underlying(underlying), counter(1), id(++storage_counter) {
	std::cout << "constructed context_ref_counter " << id << "\n";
}

void context_ref_counter::inc() {
	++counter;
}

void context_ref_counter::dec() {
	if (--counter == 0) {
		delete this;
	}
}

}}
