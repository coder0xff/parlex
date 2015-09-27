/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Brandon Sharp
 Version     :
 Copyright   : copyright (c) 2015
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libparlex/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */

#include "dfa.hpp"
#include "builtins.hpp"
#include "state_machine.hpp"
#include "parser.hpp"

int main(void) {
	parlex::dfa dfa;
	dfa.add_transition(0, parlex::any_character, 1);
	parlex::state_machine s(dfa);
	parlex::parser p;
	auto result = p.parse(s, U"a");
	return 0;
}
