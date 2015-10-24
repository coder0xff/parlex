#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include "terminal.hpp"

namespace parlex {
namespace details {

class any_character_t : public terminal {
public:
	virtual ~any_character_t() = default;
	virtual bool test(std::u32string const & document, int documentPosition) const final;
	virtual int get_length() const final;
	virtual std::string get_id() const final;
};

}

extern details::any_character_t any_character;

class string_terminal : public terminal {
public:
	string_terminal(std::u32string const & s);
	virtual ~string_terminal() = default;
	virtual bool test(std::u32string const & document, int documentPosition) const final;
	virtual int get_length() const final;
	virtual std::string get_id() const final;
private:
	std::u32string const s;
	int const length;
	std::string const id;
};

}

#endif