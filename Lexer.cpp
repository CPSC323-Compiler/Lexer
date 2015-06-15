#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"

using namespace std;

Lexer::Lexer() {

}

LexTokPair Lexer::getTokenLexemePair() {
	char next_char,
		temp;

	// open input file
	inFile.open("input.txt");

	// error checking
	if (!inFile) {
		cout << "File had trouble opening." << endl;
	}

	while (inFile) {
		inFile.get(next_char);

		while (isspace(next_char)) {
			inFile.get(next_char);
		}

		// if first char of token is a digit, go to digit/real dfsm
		if (isdigit(next_char)) {
			int state = 1, // starting state: 1
				col = 0; // initializing column to 0
			bool token_found = false, // initializing token_found to false
				leave_machine = false;
			LexTokPair pair;

			// starting state: 1
			// acceptance states: 2, 5
			int DigitOrRealTable[5][2] = { { 2, 3 }, // row 1
											{ 2, 4 }, // row 2
											{ 3, 3 }, // row 3
											{ 5, 3 }, // row 4
											{ 5, 3 }, }; // row 5

			// set machine variable to digits/reals
			machine = "dr";

			// while token is not found and it's not yet time to leave this machine
			while (!token_found && !leave_machine) {
				switch (state) {
				// states 2, 5 are acceptance states
					// changed cases to 1, 4 instead of 2, 5 b/c of off-by-one error
					// original states were numbered 1-5, not 0-4
				case 1:
					// if next char is a digit, token not found yet
					temp = next_char;
					inFile.get(next_char);
					if (isdigit(next_char)) {
						// read in next char from file, as long as it's a digit
						while (isdigit(inFile.peek())) {
							inFile.get(next_char);
							// tack on next_char to lexeme variable
							pair.lexeme += next_char;
						}
					} else {
						inFile.unget();
						next_char = temp;
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
					}
					pair.token = "integer";
					token_found = true;
					return pair;
					break;
				case 4:
					// if next char is a digit, token not found yet
					temp = next_char;
					inFile.get(next_char);
					if (isdigit(next_char)) {
						// read in next char from file, as long as it's a digit
						while (isdigit(inFile.peek())) {
							inFile.get(next_char);
							// tack on next_char to lexeme variable
							pair.lexeme += next_char;
						}
					} else {
						inFile.unget();
						next_char = temp;
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
					}
					pair.token = "real";
					token_found = true;
					return pair;
					break;
				default:
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;

					// find column for next_char
					col = findLexemeColumn(next_char);
					// get next state
					state = DigitOrRealTable[state][col];
					state--;

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
	}

	// close file
	inFile.close();
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