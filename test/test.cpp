#include "../include/safe_ptr.hpp"
#include <vector>
#include <tuple>

void safe_ptr_test(void) {
	struct T {
		T(int x) : x(x) {}
		int x;
	};
	safe_ptr<T> test = safe_ptr<T>::construct(0);
	safe_ptr<T> other = test;

	std::vector<safe_ptr<T>> v;
	std::tuple<safe_ptr<T>> t;
	std::make_tuple(other);
	v.emplace_back(other);
	v.emplace_back(safe_ptr<T>::construct(1));
}


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
	safe_ptr_test();
	parser_test_1();
}