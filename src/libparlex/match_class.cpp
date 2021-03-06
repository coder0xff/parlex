#include "match_class.hpp"

namespace parlex {

namespace details {

match_class::match_class(recognizer const & r, int documentPosition) : r(r), document_position(documentPosition) {}

bool match_class::operator <(match_class const & rhs) const {
	return document_position < rhs.document_position || 
		(document_position == rhs.document_position && &r < &rhs.r);
}

}
}