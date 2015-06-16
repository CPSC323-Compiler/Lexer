#include <iostream>
#include <string>
#include "Lexer.h"

using namespace std;

int main() {
	LexTokPair pair;
	string filename;

	cout << "Enter input file name: ";
	getline(cin, filename);

	Lexer l(filename);

	cout << "Token" << " " << "Lexeme" << endl;

	while (!l.atEndOfFile()) {
		pair = l.getTokenLexemePair();
		cout << pair.token << " " << pair.lexeme << endl;
	}
}