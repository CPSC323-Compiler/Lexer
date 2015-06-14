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
	char next_char;

	// read from input file
	inFile.open("input.txt");

	// error checking
	if (!inFile) {
		cout << "File had trouble opening." << endl;
	}

	// if next_char is a digit, go to digit/real dfsm
		// while not in an acceptance state:
			// read in next char from file
			next_char = inFile.get;
			// find column for next_char
			// get next state

			// notes:
			// distinguish between digits and reals
			// keep track of string for lexeme
			// decide on token

	// if state is accepting, token found
	// else, token not found

	// deal with the following later after first machine works
		// else if next_char is a letter, go to identifier dfsm
		// else if next_char is a known operator, go to that block
		// else if next_char is a known separator, go to that block
		// else invalid char

	// close file
	inFile.close();

	// delete this part later -- needed to build for now
	LexTokPair pair;
	pair.lexeme = "f";
	pair.token = "f";
	return pair;
}