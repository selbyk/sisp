// Special.h -- the parse tree node data structure for special forms
//
// Defines the types
//
//   class Special;
//   class Quote : public Special;
//   class Lambda : public Special;
//   class Begin : public Special;
//   class If : public Special;
//   class Let : public Special;
//   class Cond : public Special;
//   class Define : public Special;
//   class Set : public Special;
//   class Regular : public Special;

#ifndef SPECIAL_H
#define SPECIAL_H

#include <iostream>

using namespace std;

#include "Tree.h"

#ifndef NULL
#define NULL 0
#endif
#define FALSE 0
#define TRUE  1

// There are several different approaches for how to implement the Special
// hierarchy.  We'll discuss some of them in class.  The easiest solution
// is to not add any fields and to use empty constructors.

class Special
{
	public:
		virtual void print(Node * t, int n, bool p) = 0;
		string indents(int indentationNo, char c) {
			string s = "";
			s.append(indentationNo, c);
			return s;
		}
		virtual void printLiteral(Node * t, int n, bool p);
};

class Quote : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class Lambda : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class Begin : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class If : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class Let : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class Cond : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class Define : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class Set : public Special
{
	private:
		// TODO: Add any fields needed.

	public:
		// TODO: Add an appropriate constructor.

		virtual void print(Node * t, int n, bool p);
};


class Regular : public Special
{
	private:

	public:
		virtual void print(Node * t, int n, bool p);
};

#endif
