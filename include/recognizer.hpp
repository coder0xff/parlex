#ifndef RECOGNIZER_HPP
#define RECOGNIZER_HPP

namespace parlex {

class recognizer;

namespace details {
	class subjob;

	class recognizer_reference_comparer {
	public:
		inline bool operator()(recognizer const & lhs, recognizer const & rhs) { return &lhs < &rhs; }
	};
}

// encapsulates all logic, including heuristics,
// of detecting and parsing strings of a language,
// given a document and a position in that document
// the implementor can use the on method to listen for another match_class
// for each match found in the match_class, "process" is invoked, forwarding "state"
// accept is called by the implementor (from within process or halt)
// to indicate that a permutation has been found
class recognizer {
public:
	virtual ~recognizer() = default;
	inline virtual bool is_terminal() const { return false; }
};

}

#endif
