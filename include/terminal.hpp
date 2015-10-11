#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "recognizer.hpp"

namespace parlex {

class terminal : public recognizer {
public:
	virtual ~terminal() = default;

	void start(safe_ptr<details::parse_context> c) const final;
	void halt(safe_ptr<details::parse_context> c) const final;
	void inline process(safe_ptr<details::parse_context> c, int s) const final { throw "terminals are not state machines"; }
	virtual bool test(std::u32string const & document, int documentPosition) const = 0;
	virtual int get_length() const = 0;
protected:
	inline terminal() {}
private:
};

}

#endif
