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
		std::set<parlex::permutation> const & expected_permutations = pair.second;
		auto i = actual.table.find(expected_match_class);
		if (i == actual.table.end()) {
			throw "match missing";
		}
		std::set<parlex::permutation> const & actual_permutations = i->second;
		if (expected_permutations != actual_permutations) {
			throw "permutations differ";
		}
	}
}

void parser_one_character_test() {
	//setup the test input
	std::u32string document = U"a";
	parlex::dfa recognizer;
	recognizer.function[0][&parlex::any_character] = 0;

	parlex::grammar g;
	g["main"] = recognizer;

	//setup the expected value
	parlex::details::match expected_root(parlex::details::match_class(&recognizer, 0), document.length());
	parlex::abstract_syntax_graph expected(expected_root);
	parlex::details::match expected_child(parlex::details::match_class(&parlex::any_character, 0), 1);
	expected.table[expected_root].insert(parlex::permutation ({ expected_child }));
	expected.table[expected_child].insert(parlex::permutation());

	//test
	parlex::parser p;
	parlex::abstract_syntax_graph actual = p.parse(g, document);

	assert_asg(expected, actual);
}

