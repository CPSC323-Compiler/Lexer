#include <iostream>
#include <string>
#include "Lexer.h"

using namespace std;

LexTokPair Lexer::getTokenLexemePair() {
	// Starting state: 1
	// Acceptance states: 2, 5
	int DigitOrRealTable[5][2] = { { 2, 3 }, // Row 1
									{ 2, 4 }, // Row 2
									{ 3, 3 }, // Row 3
									{ 5, 3 }, // Row 4
									{ 5, 3 }, }; // Row 5

	// Starting state: 1
	// Acceptance states: 2, 4
	int IdentifierTable[5][2] = { { 2, 3 }, // Row 1
									{ 4, 5 }, // Row 2
									{ 3, 3 }, // Row 3
									{ 4, 5 }, // Row 4
									{ 4, 5 }, }; // Row 5
}