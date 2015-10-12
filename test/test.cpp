#include "dfa.hpp"
#include "builtins.hpp"
#include "state_machine.hpp"
#include "parser.hpp"

void parser_test_1() {
	parlex::dfa dfa;
	dfa.add_transition(0, parlex::any_character, 1);
	parlex::state_machine s(dfa);
	parlex::parser p;
	auto result = p.parse(s, U"a");
}

int main(void) {
	parser_test_1();
}