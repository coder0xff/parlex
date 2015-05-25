#ifndef MATCH_CATEGORY_HPP
#define MATCH_CATEGORY_HPP

namespace parlex {

class recognizer;

namespace details {

struct match_category {
	recognizer const * recognizer;
	int document_position;
	inline bool operator <(match_category const & rhs) const {
		return document_position < rhs.document_position || 
			(document_position == rhs.document_position && recognizer < rhs.recognizer);
	}
};

}
}

#endif