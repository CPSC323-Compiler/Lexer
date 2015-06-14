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
	bool token_found = false, // initializing token_found to false
		leave_machine = false;
	LexTokPair pair;

	// read from input file
	inFile.open("input.txt");

	// error checking
	if (!inFile) {
		cout << "File had trouble opening." << endl;
	}

	while (inFile) {
		// if first char of token is a digit, go to digit/real dfsm
		if (isdigit(inFile.peek())) {
			// set machine variable to digits/reals
			machine = "dr";

			// while token is not found and it's not yet time to leave this machine
			while (!token_found && !leave_machine) {
				// read in next char from file
				inFile.get(next_char);

				// if next_char is !whitespace and !digit and !period, inFile.unget()
				if (!isspace(next_char) && !isdigit(next_char) && (next_char != '.')) {
					inFile.unget();
					leave_machine = true;
				}

				switch (state) {
					// states 2, 5 are acceptance states
				case 2:
					// if next_char is a digit or period, token not found yet
					if (isdigit(inFile.peek()) || inFile.peek() == '.') {
						break;
					}
					else {
						pair.token = "integer";
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
						token_found = true;
						return pair;
					}
					break;
				case 5:
					// if next_char is a digit, token not found yet
					if (isdigit(inFile.peek())) {
						break;
					}
					else {
						pair.token = "real";
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
						token_found = true;
						return pair;
					}
					break;
				default:
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;

					// find column for next_char
					col = findLexemeColumn(next_char);
					// get next state
					state = DigitOrRealTable[state][col];
					break;
				}
			}
		}

		// deal with the following later after first machine works
		// else if next_char is a letter, go to identifier dfsm
		// else if next_char is a known operator, go to that block
		// else if next_char is a known separator, go to that block
		// else invalid char
	}

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