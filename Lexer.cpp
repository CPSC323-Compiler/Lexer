#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"

using namespace std;

Lexer::Lexer(string file_name) {
	inFile.open(file_name.c_str());

	if (!inFile.is_open()){
		cout << "Error: File won't open." << endl;
	}
}

LexTokPair Lexer::getTokenLexemePair() {
	char next_char;

	inFile.get(next_char);

	while (isspace(next_char)) {
		inFile.get(next_char);
	}

	// if first char of token is a digit, go to digit/real dfsm
	if (isdigit(next_char)) {
		int state = 0, // starting state: 0
			col = 0; // initializing column to 0
		bool token_found = false,
			leave_machine = false;
		LexTokPair pair;

		// starting state: 0
		// acceptance states: 1, 4
		int DigitOrRealTable[5][2] = { { 1, 2 }, // row 1
										{ 1, 3 }, // row 2
										{ 2, 2 }, // row 3
										{ 4, 2 }, // row 4
										{ 4, 2 }, }; // row 5

		// set machine variable to digits/reals
		machine = "dr";

		// while token is not found and it's not yet time to leave this machine
		while (!token_found && !leave_machine) {
			switch (state) {
			// states 1, 4 are acceptance states
				// original states were numbered 1-5, not 0-4
			case 1:
				// tack on next_char to lexeme variable
				pair.lexeme += next_char;
				// if next char is a digit, token not found yet
				if (isdigit(inFile.peek())) {
					inFile.get(next_char);
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
					// read in next char from file, as long as it's a digit
					while (isdigit(inFile.peek())) {
						inFile.get(next_char);
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
					}
				} else {
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
				}
				pair.token = "integer";
				token_found = true;
				return pair;
				//break;
			case 4:
				// tack on next_char to lexeme variable
				pair.lexeme += next_char;
				// if next char is a digit, token not found yet
				if (isdigit(inFile.peek())) {
					inFile.get(next_char);
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
					// read in next char from file, as long as it's a digit
					while (isdigit(inFile.peek())) {
						inFile.get(next_char);
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
					}
				} else {
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
				}
				pair.token = "real";
				token_found = true;
				return pair;
				//break;
			default:
				// tack on next_char to lexeme variable
				pair.lexeme += next_char;

				// find column for next_char
				col = findLexemeColumn(next_char);
				// get next state
				state = DigitOrRealTable[state][col];

				// read in next char from file
				inFile.get(next_char);
				break;
			}

			if (!isspace(next_char) && !isdigit(next_char) && (next_char != '.')) {
				leave_machine = true;
			}
		}
	}
	/*
	// if first char of token is a letter, go to identifer dfsm
	else if (isalpha(next_char)) {
		int state = 1, // starting state: 1
			col = 0; // initializing column to 0
		char next_char;
		bool token_found = false, // initializing token_found to false
			leave_machine = false;
		LexTokPair pair;

		// starting state: 1
		// acceptance states: 2, 4
		int IdentifierTable[5][2] = { { 2, 3 }, // row 1
										{ 4, 5 }, // row 2
										{ 3, 3 }, // row 3
										{ 4, 5 }, // row 4
										{ 4, 5 }, }; // row 5

		// delete later
		return pair;
	}*/

	// else if next_char is a known operator, go to that block
	// else if next_char is a known separator, go to that block
	// else invalid char

	// close file
	inFile.close();
}

int Lexer::findLexemeColumn(char some_char) {
	if (machine == "dr") {
		if (isdigit(some_char)) {
			return 0;
		} else {
			return 1;
		}
	}
	else {
		if (isalpha(some_char)) {
			return 0;
		} else {
			return 1;
		}
	}
}

bool Lexer::isSeparator(char) {
	// delete later
	return true;
}

bool Lexer::isOperator(char) {
	// delete later
	return true;
}

bool Lexer::isKeyword(string) {
	// delete later
	return true;
}

bool Lexer::atEndOfFile() {
	if (!inFile) {
		return true;
	} else {
		return false;
	}
}