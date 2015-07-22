#include <string>

#include "parser.hpp"
#include "builtins.hpp"

void assert_asg(parlex::abstract_syntax_graph const & expected, parlex::abstract_syntax_graph const & actual) {
	if (expected.root < actual.root || actual.root < expected.root) {
		throw "root differs";
	}

	if (expected.table.size() != actual.table.size()) {
		throw "the table size differs";
	}

	for (auto const & pair : expected.table) {
		auto const & expected_match_class = pair.first;
		std::set<parlex::match> const & expected_matches = pair.second;
		auto i = actual.table.find(expected_match_class);
		if (i == actual.table.end()) {
			throw "match_class missing";
		}
		std::set<parlex::match> const & actual_matches = i->second;
		if (expected_matches != actual_matches) {
			throw "matches differ";
		}
	}
}

void parser_one_character_test() {
	std::u32string document = U"a";

	parlex::dfa recognizer;
	recognizer.function[0][&parlex::any_character] = 0;

	parlex::grammar g;
	g["main"] = recognizer;

	parlex::details::match_class expected_root(parlex::details::match_category(&recognizer, 0), document.length());
	parlex::abstract_syntax_graph expected(expected_root);
	parlex::details::match_class expected_child(parlex::details::match_category(&parlex::any_character, 0), 1);
	expected.table[expected_root].insert(parlex::match ({ expected_child }));
	expected.table[expected_child].insert(parlex::match());

	parlex::parser p;
	parlex::abstract_syntax_graph actual = p.parse(g, document);

	assert_asg(expected, actual);
}
