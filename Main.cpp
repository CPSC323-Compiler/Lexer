#include <iostream>
#include "Lexer.h"

using namespace std;

int main() {
	LexTokPair pair;
	Lexer l;

	cout << "Token" << " " << "Lexeme" << endl;
	pair = l.getTokenLexemePair();
	cout << pair.token << " " << pair.lexeme << endl;
	pair = l.getTokenLexemePair();
	cout << pair.token << " " << pair.lexeme << endl;
	pair = l.getTokenLexemePair();
	cout << pair.token << " " << pair.lexeme << endl;
}