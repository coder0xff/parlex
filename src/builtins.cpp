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

}