#include "terminal.hpp"

#include "parse_context.hpp"
#include "subjob.hpp"
#include "job.hpp"

namespace parlex {

void terminal::start(details::parse_context const & c) const {
	if (test(c.owner.owner.document, c.current_document_position)) {
		details::parse_context end = c;
		end.current_document_position += get_length();
		accept(end);
	}
}

void terminal::halt(details::parse_context const & c) const { 
	recognizer::halt(c);
}

}