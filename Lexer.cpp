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
	bool not_invalid = false;

	inFile.get(next_char);

	// skip whitespace
	while (isspace(next_char)) {
		inFile.get(next_char);
	}

	// if first char of token is a 2-char operator
	if (((next_char == '=' || next_char == '!' || next_char == '<'
		|| next_char == '>') && inFile.peek() == '=')) {
		LexTokPair pair;
		pair.lexeme += next_char;
		inFile.get(next_char);
		pair.lexeme += next_char;
		pair.token = "operator";
		return pair;
	}

	// if first char of token is a single-char operator
	else if (isOperator(next_char)) {
		LexTokPair pair;
		pair.lexeme += next_char;
		pair.token = "operator";
		return pair;
	}

	// if first char of token is a 2-char separator
	else if ((next_char == '$') && (inFile.peek() == '$')) {
		LexTokPair pair;
		pair.lexeme += next_char;
		inFile.get(next_char);
		pair.lexeme += next_char;
		pair.token = "separator";
		return pair;
	}
	
	// if first char of token is a separator
	else if (isSeparator(next_char)) {
		LexTokPair pair;
		pair.lexeme += next_char;
		pair.token = "separator";
		return pair;
	}

	// if first char of token is an invalid/unknown char
	else if ((next_char == '.')
		|| (!isSeparator(next_char) && !isOperator(next_char) && !isalnum(next_char))) {
		LexTokPair pair;
		pair.lexeme += next_char;
		if (next_char == '.' && isdigit(inFile.peek())) {
			while (isdigit(inFile.peek())) {
				inFile.get(next_char);
				pair.lexeme += next_char;
			}
		}
		pair.token = "invalid";
		return pair;
	}

	// if first char of token is a digit, go to digit/real dfsm
	else if (isdigit(next_char)) {
		int state = 0, // starting state: 0
			col = 0; // initializing column to 0
		bool token_found = false,
			leave_machine = false;
		LexTokPair pair;

		// starting state: 0
		// acceptance states: 1, 4
		int DigitOrRealTable[5][2] = { { 1, 2 }, // row 0
										{ 1, 3 }, // row 1
										{ 2, 2 }, // row 2
										{ 4, 2 }, // row 3
										{ 4, 2 }, }; // row 4

		// set machine variable to digits/reals
		machine = "dr";

		// while token is not found and it's not yet time to leave this machine
		while (!token_found) {
			switch (state) {
			// states 1, 4 are acceptance states
				// original states were numbered 1-5, not 0-4
			case 1:
				// if char is . then need to go to state 4
				if (next_char == '.') {
					state = 4;
					break;
				}
				// if next char in stream is not EOF and next_char is valid
				if ((inFile.peek() != EOF) && not_invalid) {
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
					// if next char is a digit, token not found yet
					while (isdigit(inFile.peek())) {
						inFile.get(next_char);
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
					}
				}
				// if next char in stream is a period, then go to state 4 for real numbers
				if (inFile.peek() == '.') {
					inFile.get(next_char);
					state = 4;
					break;
				}
				pair.token = "integer";
				token_found = true;
				return pair;
				//break;
			case 2: // only invalid lexemes transition to state 2
				pair.lexeme += next_char;
				while (isdigit(inFile.peek()) || (inFile.peek() == '.')) {
					inFile.get(next_char);
					pair.lexeme += next_char;
				}
				pair.token = "invalid";
				return pair;
				//break;
			case 4:
				// if next char is a digit, token not found yet
				if (isdigit(inFile.peek())) {
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
					// read in next char from file
					inFile.get(next_char);
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
					// read in next char from file, as long as it's a digit
					while (isdigit(inFile.peek())) {
						inFile.get(next_char);
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
					}
				}
				// else lexeme is invalid/unknown
				else {
					state = 2;
					break;
				}
				if (inFile.peek() == '.') {
					state = 2;
					inFile.get(next_char);
					break;
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

				// if next char is a digit or period, read in next char from file
				if (!isInvalid(inFile.peek()) && !isspace(inFile.peek()) && !isalpha(inFile.peek())
					&& !isOperator(inFile.peek()) && !isSeparator(inFile.peek())) {
					inFile.get(next_char);
					not_invalid = true;
				}
				break;
			}
		}
	}

	// if first char of token is a letter, go to identifer dfsm
	else if (isalpha(next_char)) {
		int state = 0, // starting state: 0
			col = 0; // initializing column to 0
		bool token_found = false,
			leave_machine = false;
		LexTokPair pair;

		// starting state: 0
		// acceptance states: 1, 3
		int IdentifierTable[5][2] = { { 1, 2 }, // row 0
										{ 3, 4 }, // row 1
										{ 2, 2 }, // row 2
										{ 3, 4 }, // row 3
										{ 3, 4 }, }; // row 4

		machine = "id";

		// while token is not found and it's not yet time to leave this machine
		while (!token_found) {
			switch (state) {
				// states 1, 3 are acceptance states
				// original states were numbered 1-5, not 0-4
			case 1:
				// if not a single char identifier
				if (isalpha(inFile.peek())) {
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
					// get next char
					inFile.get(next_char);
					state = 3;
					break;
				}
				else if (isdigit(inFile.peek())) {
					state = 3;
					break;
				}
				if (inFile.peek() != EOF && not_invalid) {
					// tack on next_char to lexeme variable
					pair.lexeme += next_char;
				}
				// if lexeme is a keyword
				if (isKeyword(pair.lexeme)) {
					pair.token = "keyword";
				} else {
					pair.token = "identifier";
				}
				token_found = true;
				return pair;
				//break;
			case 2: // only invalid lexemes transition to state 2
				pair.lexeme += next_char;
				pair.token = "invalid";
				return pair;
				//break;
			case 3:
				// tack on next_char to lexeme variable
				pair.lexeme += next_char;
				if (inFile.peek() != EOF && not_invalid) {
					// if next char is a letter or digit, token not found yet
					while (isalnum(inFile.peek())) {
						// get next char
						inFile.get(next_char);
						/*if (isdigit(next_char) && !isalnum(inFile.peek())) {
							pair.lexeme += next_char;
							pair.token = "invalid";
							return pair;
						}*/
						// tack on next_char to lexeme variable
						pair.lexeme += next_char;
					}
				}
				if (isdigit(next_char)) {
					pair.token = "invalid";
					return pair;
				}
				// if lexeme is a keyword
				if (isKeyword(pair.lexeme)) {
					pair.token = "keyword";
				}
				else {
					pair.token = "identifier";
				}
				token_found = true;
				return pair;
				//break;
			default:
				// tack on next_char to lexeme variable
				pair.lexeme += next_char;

				// find column for next_char
				col = findLexemeColumn(next_char);
				// get next state
				state = IdentifierTable[state][col];

				// if next char is a digit or letter, read in next char from file
				if (!isInvalid(inFile.peek()) && !isspace(inFile.peek()) && (inFile.peek() != '.')
					&& !isSeparator(inFile.peek()) && !isOperator(inFile.peek())) {
					inFile.get(next_char);
					not_invalid = true;
				}
				break;
			}
		}
	}
}

int Lexer::findLexemeColumn(char some_char) {
	if (machine == "dr") {
		if (isdigit(some_char)) {
			return 0;
		} else {
			return 1;
		}
	} else {
		if (isalpha(some_char)) {
			return 0;
		} else {
			return 1;
		}
	}
}

bool Lexer::isInvalid(char some_char) {
	return (!
		(isSeparator(some_char)
		|| isOperator(some_char)
		|| isalnum(some_char)
		|| (some_char == '.')
		));
}

bool Lexer::isSeparator(char c) {
	return (
		c == '('
		|| c == ')'
		|| c == ';'
		|| c == ','
		|| c == '{'
		|| c == '}'
	);
}

bool Lexer::isOperator(char c) {
	return (
		c == '='
		|| c == '!'
		|| c == '<'
		|| c == '>'
		|| c == '+'
		|| c == '-'
		|| c == '*'
		|| c == '/'
	);
}

bool Lexer::isKeyword(string input) {
	return (
		input == "function"
		|| input == "return"
		|| input == "integer"
		|| input == "int"
		|| input == "real"
		|| input == "boolean"
		|| input == "if"
		|| input == "fi"
		|| input == "else"
		|| input == "read"
		|| input == "write"
		|| input == "while"
		|| input == "for"
	);
}

bool Lexer::atEndOfFile() {
	if (!inFile) {
		return true;
	} else {
		return false;
	}
}

void Lexer::closeFile() {
	inFile.close();
}