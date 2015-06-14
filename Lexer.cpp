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

	int state = 1, // starting state: 1
		col = 0, // initializing column to 0
		state = 0; // initializing state to 0
	char next_char;
	bool token_found = false; // initializing token_found to false
	LexTokPair pair;

	// read from input file
	inFile.open("input.txt");

	// error checking
	if (!inFile) {
		cout << "File had trouble opening." << endl;
	}

	// read in first char into next_char
	inFile.get(next_char);

	// if next_char is a digit, go to digit/real dfsm
	if (isdigit(next_char)) {
		// set machine variable to digits/reals
		machine = "dr";
		// loop around until next_char is !digit and !period and !eof
		while ((isdigit(next_char) || (next_char == '.')) && (!inFile)) {
			// read in next char from file
			inFile.get(next_char);
			// tack on next_char to lexeme variable
			pair.lexeme += next_char;
			// if next_char is a period, then token is real
			if (next_char == '.') {
				pair.token = "real";
			}
			// find column for next_char
			col = findLexemeColumn(next_char);
			// get next state
			state = DigitOrRealTable[state][col];
		}

		// if next_char is !whitespace, inFile.unget()
		// if state is accepting, token_found = true
			// if token is "", then token is digit
			// return token-lexeme pair
		// else, token_found = false
	}

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

int Lexer::findLexemeColumn(char some_char) {
	if (machine == "dr") {
		if (isdigit(some_char)) {
			return 1;
		} else {
			return 2;
		}
	}
	else {
		if (isalpha(some_char)) {
			return 1;
		} else {
			return 2;
		}
	}
}

bool Lexer::isSeparator(char) {

}

bool Lexer::isOperator(char) {

}

bool Lexer::isKeyword(string) {

}