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
	int const id;
public:
	context();
	context(subjob & owner, context const & prior, int const document_position, match const * from_transition);
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


}
}

#endif
