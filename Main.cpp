#include <iostream>
#include "Lexer.h"

using namespace std;

int main() {
	LexTokPair pair;
	Lexer l;

	cout << "Token" << " " << "Lexeme" << endl;
	//while (!l.atEndOfFile()) {
		pair = l.getTokenLexemePair();
		cout << pair.token << " " << pair.lexeme << endl;
	//}
}