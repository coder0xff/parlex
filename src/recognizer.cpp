#include "recognizer.hpp"

#include "parse_context.hpp"
#include "job.hpp"
#include "subjob.hpp"

namespace parlex {

void recognizer::halt(safe_ptr<details::parse_context> c) const {
}

void recognizer::accept(safe_ptr<details::parse_context> c) const {
	c->owner.on_recognizer_accepted(c->current_document_position - c->owner.document_position, c->result());
}

//hook up an event handler
void recognizer::on(safe_ptr<details::parse_context> c, recognizer const & r, int nextDfaState) const {
	c->owner.owner.connect(details::match_class(r, c->current_document_position), c, nextDfaState);
}

}
