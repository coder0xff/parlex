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
	std::cout << result.to_dot() << std::endl;
}

void parser_test_2() {
	parlex::dfa dfa;
	parlex::string_terminal helloWorld(U"Hello, world!");
	dfa.add_transition(0, helloWorld, 1);
	parlex::state_machine s("machine", dfa);
	parlex::parser p(1);
	parlex::abstract_syntax_graph result = p.parse(s, U"Hello, world!");
	std::cout << result.to_dot() << std::endl;
}

void parser_test_3() {
	parlex::dfa dfa;
	parlex::string_terminal helloWorld(U"Foo");
	dfa.add_transition(0, helloWorld, 1);
	dfa.accept_state_count = 1;
	parlex::state_machine s("machine", dfa);
	parlex::parser p(1);
	parlex::abstract_syntax_graph result = p.parse(s, U"bar");
	std::cout << result.to_dot() << std::endl;
}

void parser_test_4() {
	parlex::dfa dfa;
	parlex::string_terminal hello(U"Hello");
	parlex::string_terminal world(U", world");
	dfa.add_transition(0, hello, 1);
	dfa.add_transition(1, world, 2);
	dfa.add_transition(2, parlex::any_character, 3);
	dfa.accept_state_count = 2;
	parlex::state_machine s("machine", dfa);
	parlex::parser p(1);
	parlex::abstract_syntax_graph result = p.parse(s, U"Hello, world!");
	std::cout << result.to_dot() << std::endl;
}

int main(void) {
	//parser_test_1();
	//parser_test_2();
	//parser_test_3();
	parser_test_4();
}