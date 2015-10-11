#include "terminal.hpp"

#include "parse_context.hpp"
#include "subjob.hpp"
#include "job.hpp"

namespace parlex {

void terminal::start(safe_ptr<details::parse_context> c) const {
	if (test(c->owner.owner.document, c->current_document_position)) {
		accept(c, get_length());
	}
}

void terminal::halt(safe_ptr<details::parse_context> c) const {
	recognizer::halt(c);
}

}
