#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"

using namespace std;

Lexer::Lexer() {

}

LexTokPair Lexer::getTokenLexemePair() {
	// starting state: 1
	// acceptance states: 2, 5
	int DigitOrRealTable[5][2] = { { 2, 3 }, // row 1
									{ 2, 4 }, // row 2
									{ 3, 3 }, // row 3
									{ 5, 3 }, // row 4
									{ 5, 3 }, }; // row 5

	// starting state: 1
	// acceptance states: 2, 4
	int IdentifierTable[5][2] = { { 2, 3 }, // row 1
									{ 4, 5 }, // row 2
									{ 3, 3 }, // row 3
									{ 4, 5 }, // row 4
									{ 4, 5 }, }; // row 5

	int state = 1; // starting state: 1

	// read from input file
	inFile.open("input.txt");

	if (inFile) {
		cout << "Success!" << endl;
	}

	// close file
	inFile.close();

	// delete this part later -- needed to build for now
	LexTokPair pair;
	pair.lexeme = "f";
	pair.token = "f";
	return pair;
}