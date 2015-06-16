#include <iostream>
#include <string>
#include <iomanip>
#include "Lexer.h"

using namespace std;

int main() {
	LexTokPair pair;
	string filename;

	cout << "Enter input file name: ";
	getline(cin, filename);

	Lexer l(filename);

	cout << "Token" << "\t\t\t" << "Lexeme" << endl;

	while (!l.atEndOfFile()) {
		pair = l.getTokenLexemePair();
		cout << pair.token << setw(18) << pair.lexeme << endl;
	}
}