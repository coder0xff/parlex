#ifndef BUILTINS_HPP
#define BUILTINS_HPP

#include "terminal.hpp"

namespace parlex {
namespace details {

class any_character_t : public terminal {
public:
	virtual ~any_character_t() = default;
	virtual bool test(std::u32string const & document, int documentPosition) const;
	virtual int get_length() const;
	virtual std::string get_id() const;
};

}

extern details::any_character_t any_character;

}

#endif