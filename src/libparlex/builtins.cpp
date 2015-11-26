#include <sstream>

#include "builtins.hpp"
#include "uni_trunc.hpp"

namespace parlex {
namespace details {

bool any_character_t::test(std::u32string const & document, int documentPosition) const {
	return documentPosition < document.length();
}

int any_character_t::get_length() const {
	return 1;
}

std::string any_character_t::get_id() const {
	return "any_character";
}

}

namespace builtins {

parlex::details::any_character_t any_character;

string_terminal::string_terminal(std::u32string const & s) : s(s), length(s.length()), id(uni_trunc(s)) {}

bool string_terminal::test(std::u32string const & document, int const documentPosition) const {
	return document.compare(documentPosition, length, s) == 0;
}

int string_terminal::get_length() const {
	return length;
}

std::string string_terminal::get_id() const {
	return id;
}

}
}