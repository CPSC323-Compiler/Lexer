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
	Lexer();
	// i'm keeping this here for now

	LexTokPair getTokenLexemePair();
	// if file input is valid, returns lexeme-token pair

	bool isSeparator(char);
	// if character is a separator, returns true
	// this function also checks if the character is a part of the separator "<-"

	bool isOperator(char);
	// if character is an operator, returns true

	bool isKeyword(string);
	// if the identifier string is a keyword, returns true

	int findLexemeColumn(char);
	// depending on what the character is, this function returns the corresponding column of the 2D array
private:
	ifstream inFile;
	string token,
		lexeme;
};