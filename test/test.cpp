#include <iostream>

#include "dfa.hpp"
#include "builtins.hpp"
#include "state_machine.hpp"
#include "parser.hpp"
#include "abstract_syntax_graph.hpp"

void parser_test_1() {
	parlex::dfa dfa;
	dfa.add_transition(0, parlex::any_character, 1);
	parlex::state_machine s("machine", dfa);
	parlex::parser p(1);
	parlex::abstract_syntax_graph result = p.parse(s, U"a");
	std::cout << result.to_dot();
}

int main(void) {
	parser_test_1();
}