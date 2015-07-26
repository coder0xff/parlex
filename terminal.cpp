#include "terminal.hpp"

namespace parlex {

void terminal::start(details::parse_context const & c) const final {
	if (test(c.owner.owner.document, c.current_document_position)) {
		parse_context end = c;
		end.current_document_position += get_length();
		accept(end);
	}
}

void terminal::halt(details::parse_context const & c) const final { 
	recognizer::halt(); 
}

}