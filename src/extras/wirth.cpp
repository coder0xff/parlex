#include "wirth.hpp"

namespace parlex {
namespace wirth {

namespace {
	grammar build() {
		parlex::string_terminal period(U".");
		parlex::string_terminal openBracket(U"{");
		parlex::string_terminal closeBracket(U"}");

		parlex::dfa syntaxDfa;
		parlex::dfa productionDfa;
		parlex::dfa expressionDfa;
		parlex::dfa termDfa;
		parlex::dfa factorDfa;
		parlex::dfa identifierDfa;
		parlex::dfa literalDfa;

		
	}
}	

}
}