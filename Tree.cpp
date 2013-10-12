// Tree.cpp -- the implementation of the tree classes

#include "Tree.h"
#include "Special.h"


void BoolLit::print(int n, bool includeNewline)
{
	printIndent(n);
	cout << (boolVal ? "#t" : "#f");
	if (includeNewline)
		cout << endl;
}


void IntLit::print(int n, bool includeNewline)
{
	printIndent(n);
	cout << intVal;
	if (includeNewline)
		cout << endl;
}


void StrLit::print(int n, bool includeNewline)
{
	printIndent(n);
	cout << '"' << strVal << '"';
	if (includeNewline)
		cout << endl;
}


void Ident::print(int n, bool includeNewline)
{
	printIndent(n);
	cout << name;
	if (includeNewline)
		cout << endl;
}

void Nil::print(int n, bool p)
{
	printIndent(n);
	cout << (p ? "()" : ")");
}

void Cons::print(int n)
{
	form->print(this, n, FALSE);
}

void Cons::print(int n, bool p)
{
	form->print(this, n, p);
}

void Cons::parseList()
{
	if (car->isSymbol()) {
		string name = car->getName();
		if (name == "quote") form = new Quote();
		else if (name == "lambda") form = new Lambda();
		else if (name == "begin") form = new Begin();
		else if (name == "if") form = new If();
		else if (name == "let") form = new Let();
		else if (name == "cond") form = new Cond();
		else if (name == "define") form = new Define();
		else if (name == "setA") form = new Set();
		else form = new Regular();
	} else {
		form = new Regular();
	}
}
