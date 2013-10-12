// Scanner.cpp -- the implementation of class Scanner

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stack>
#include <cmath>

#include "Scanner.h"

Scanner::Scanner(istream * i)
{
	in = i;
	buffer = new char[BUFFERSIZE];
	size = 0;
}

void Scanner::clearBuffer()
{
	size = 0;
	delete buffer;
	buffer = new char[BUFFERSIZE];
	buffer[size] = '\0';
}

Token * Scanner::getNextToken()
{
	char ch;

	// It would be more efficient if we'd maintain our own input buffer
	// and read characters out of that buffer, but reading individual
	// characters from the input stream is easier.
	in->get(ch);

	// skip white space
	/* white space:
	  space = ' ',
	  tab = '\t'  == horizontal tab; '\v' = vertical tab
	  newline = '\n'
	  carriage-return = '\r'
	  form-feed = '\f'
	*/
	if (ch == ' ' || ch == '\t' || ch == '\v' || ch == '\n' || ch == '\r' || ch == '\f')
		return getNextToken();

	// skip comments
	if (ch == ';') {
		while (!(ch == '\n'))
			in->get(ch);
		return getNextToken();
	}

	if (in->eof())
		return NULL;

	// Special characters
	else if (ch == '\'')
		return new Token(QUOTE);
	else if (ch == '(')
		return new Token(LPAREN);
	else if (ch == ')')
		return new Token(RPAREN);
	else if (ch == '.')
		// We ignore the special identifier `...'.
		return new Token(DOT);

	// Boolean constants
	else if (ch == '#') {
		in->get(ch);
		if (ch == 't')
			return new Token(TRUET);
		else if (ch == 'f')
			return new Token(FALSET);
		else {
			cerr << "Illegal character '" << ch << "' following #" << endl;
			return getNextToken();
		}
	}

	// String constants
	else if (ch == '"') {
		in->get(ch);
		clearBuffer();
		while (ch != '"') {
			buffer[size++] = ch;
			in->get(ch);
		}
		buffer[size] = '\0';
		StrToken * stringToken = new StrToken(buffer);

		return stringToken;
	}

	// Integer constants
	else if (ch >= '0' && ch <= '9') {
		std::stack<int> s;

		do {
			s.push((int)(ch - '0'));
			in->get(ch);
		} while (ch >= '0' && ch <= '9');

		int intValue = 0;
		int i = 0;
		while (!s.empty()) {
			intValue += s.top() * pow(10.0, i++);
			s.pop();
		}
		// put the character after the integer back into the input
		in->putback(ch);
		return new IntToken(intValue);
	}

	// Identifiers
	else if (ch >= 'A' && ch <= 'z') {
		clearBuffer();
		do {
			buffer[size++] = (ch < 'a') ? ch + ('a' - 'A') : ch;
			in->get(ch);
		} while (ch >= 'a' && ch <= 'z');
		buffer[size] = '\0';
		IdentToken * identityToken = new IdentToken(buffer);

		// put the character after the integer back into the input
		in->putback(ch);
		return identityToken;
	}

	// Extended alphabet characters
	else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
	         ch == '!' || ch == '$' || ch == '%' || ch == '&' ||
	         ch == '^' || ch == '_' || ch == '~' ||
	         (ch >= 58 && ch <= 64)) {
		char arr[] = { ch, 0 };
		return new IdentToken(arr);
	}

	// Illegal character
	else {
		cerr << "Illegal input character '" << ch << '\'' << endl;
		return getNextToken();
	}
}
