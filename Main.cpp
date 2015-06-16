#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "Lexer.h"

using namespace std;

int main() {
	LexTokPair pair;
	string filename;
	ofstream outFile;

	// create file to print to
	outFile.open("out.txt");

	cout << "Enter input file name: ";
	getline(cin, filename);

	Lexer l(filename);

	outFile << "Token" << "\t\t\t" << "Lexeme" << endl;

	while (!l.atEndOfFile()) {
		pair = l.getTokenLexemePair();
		outFile << pair.token << setw(18) << pair.lexeme << endl;
	}

	// close file
	outFile.close();
}