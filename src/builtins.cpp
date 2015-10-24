#include <sstream>

#include "builtins.hpp"

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

details::any_character_t any_character;

std::string uni_trunc(std::u32string const & s) {
	std::stringstream result;
	for (char32_t const & c : s) {
		if ((int32_t)c < 0x100) {
			result << (char)(int32_t)c;
		} else {
			result << "?";
		}
	}
	return result.str();
}

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