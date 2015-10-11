#ifndef RECOGNIZER_HPP
#define RECOGNIZER_HPP

#include <safe_ptr.hpp>

namespace parlex {

class recognizer;

namespace details {
	struct parse_context;

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
	// subscribes to a match_class (from r, and the doc position in c)
	// For each match found in the match_class, "process" is invoked, forwarding "nextDfaState".
	void on(safe_ptr<details::parse_context> c, recognizer const & r, int nextDfaState) const;

	// submit a new permutation from c.permutation_builder
	void accept(safe_ptr<details::parse_context> c) const;

	void accept(safe_ptr<details::parse_context> prior, int consumedCharacterCount) const;
	
	// handler invoked when the specified parse_context is starting
	virtual void start(safe_ptr<details::parse_context> c) const = 0;

	// handler invoked when the specified parse_context will no longer process states
	virtual void halt(safe_ptr<details::parse_context> c) const;

	// handler invoked when a subscription has a new match
	// c.current_document_position and c.permutation_builer are updated
	virtual void process(safe_ptr<details::parse_context> c, int nextDfaState) const = 0;
};

}

#endif
