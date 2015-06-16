#pragma once

#include <string>
#include <fstream>

using namespace std;

struct LexTokPair {
	string token,
		lexeme;
};

class Lexer {
public:
	Lexer(string file_name);
	//

	LexTokPair getTokenLexemePair();
	// if file input is valid, returns lexeme-token pair

	int findLexemeColumn(char);
	// depending on what the character is, this function returns the corresponding column of the 2D array

	bool isSeparator(char);
	// if character is a separator, returns true
	// this function also checks if the character is a part of the separator "<-"

	bool isOperator(char);
	// if character is an operator, returns true

	bool isKeyword(string);
	// if the identifier string is a keyword, returns true

	bool atEndOfFile();
	// if at end of file, returns true

private:
	ifstream inFile;
	string machine = ""; // digits/reals (dr) or identifiers (id) machine?
};