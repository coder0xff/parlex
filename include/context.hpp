#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include <memory>
#include <vector>
#include <atomic>

#include "match.hpp"
#include "match_class.hpp"

namespace parlex {
namespace details {

class subjob;
struct context_ref_counter;

class context {
	context_ref_counter* rc;
	bool is_owner;

public:
	context();
	context(subjob & owner, context const prior, int const document_position, match const * from_transition);
	context(context const & other);
	context(context&& move);
	~context();
	context & operator =(context const & other);

	std::vector<match> result() const;
	bool is_null() const;

	subjob & owner() const;
	context prior() const;
	int current_document_position() const;
	//unique_ptr servees as optional
	std::unique_ptr<match> from_transition() const;
};

struct context_storage {
	context_storage(subjob & owner, context const prior, int const document_position, match const * from_transition);
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

	inline context_ref_counter(context_storage * underlying) : underlying(underlying), counter(1) {}

	inline void inc() {
		++counter;
	}

	inline void dec() {
		if (--counter == 0) {
			delete this;
		}
	}
};


}
}

#endif
