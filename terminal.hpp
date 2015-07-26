#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "recognizer.hpp"

namespace parlex {

class terminal : public recognizer {
public:
	virtual ~terminal() = default;

	void start(details::parse_context const & c) const final;

	void halt(details::parse_context const & c) const final;

	virtual bool test(std::u32string const & document, int documentPosition) const = 0;
	virtual int get_length() const = 0;
protected:
	inline terminal() {}
private:
};

}

#endif