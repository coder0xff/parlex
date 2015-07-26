#ifndef RECOGNIZER_HPP
#define RECOGNIZER_HPP

#include <memory>

namespace parlex {
namespace details {
	struct parse_context;
}

// encapsulates all logic, including heuristics,
// of detecting and parsing strings of a language,
// given a document and a position in that document
class recognizer {
public:
	virtual ~recognizer() = default;
	virtual void start(details::parse_context const & c) const = 0;
	virtual void halt(details::parse_context const & c) const;

	void on(details::parse_context const & c, recognizer const & r, std::function<void (details::parse_context const & c)> f) const;
	virtual void accept(details::parse_context const & c);
};

}

#endif