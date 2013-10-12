// Scanner.h -- the interface for class Scanner
//
// Defines
//
//   class Scanner;

#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include "Tokens.h"

using namespace std;

// maximum length of strings and identifiers
#define BUFFERSIZE 1000

class Scanner
{
	private:
		istream * in;
		int size;
		char * buffer;
		void clearBuffer();

	public:
		Scanner(istream * i);
		Token * getNextToken();
};

#endif
