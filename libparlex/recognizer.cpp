#include "recognizer.hpp"

#include "parse_context.hpp"
#include "job.hpp"
#include "subjob.hpp"

namespace parlex {

void recognizer::halt(details::parse_context const & c) const {
}

void recognizer::accept(details::parse_context const & c) const {
	c.owner.on_recognizer_accepted(c.current_document_position - c.owner.document_position, c.permutation_builder);
}

//hook up an event handler
void recognizer::on(details::parse_context const & c, recognizer const & r, int nextDfaState) const {
	c.owner.owner.connect(details::match_class(r, c.current_document_position), c, nextDfaState);
}

}
