#ifndef MATCH_CLASS_HPP
#define MATCH_CLASS_HPP

namespace parlex {

class recognizer;

namespace details {

struct match_class {
	recognizer const * recognizer;
	int document_position;

	inline match_class(class recognizer const * recognizer, int documentPosition) : recognizer(recognizer), document_position(documentPosition) {}

	inline bool operator <(match_class const & rhs) const {
		return document_position < rhs.document_position || 
			(document_position == rhs.document_position && recognizer < rhs.recognizer);
	}
};

}
}

#endif