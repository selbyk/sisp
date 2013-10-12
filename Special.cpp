// Special.cpp -- the implementation of the special form classes

#include "Special.h"

void Special::printLiteral(Node * node, int n, bool p)
{
	if (node->isSymbol())
		cout << indents(n, ' ') << node->getName();
	else if (node->isNumber())
		cout << indents(n, ' ') << node->getIntVal();
	else if (node->isString())
		cout << indents(n, ' ') << "\"" << node->getStrVal() << "\"";
	else
		cout << "Invalid expression";
}

void Quote::print(Node * t, int n, bool p)
{
	Node * cdr = t->getCdr();
	cout << '\'';
	cdr->getCar()->print(n, TRUE);
	cout << endl;
}

void Lambda::print(Node * t, int n, bool p)
{
	cout << "(lambda ";
	Node * second_element = t->getCdr()->getCar();
	if (second_element->isPair())
		second_element->print(n, p);
	else
		cout << "Invalid expression";

	cout << endl;

	Node * third_cons = t->getCdr()->getCdr();
	if (third_cons->isPair())
		third_cons->print(n, TRUE);
	else
		cout << "Invalid expression" << endl;

	cout << endl;
}

void Begin::print(Node * t, int n, bool p)
{
	cout << "(begin" << endl;
	Node * cdr = t->getCdr();
	if (cdr != NULL)
		cdr->print(n, p);
	cout << endl;
}

void If::print(Node * t, int n, bool p)
{
	cout << indents(n, ' ');
	cout << "(if ";

	//print condition clause
	Node * condition_clause = t->getCdr()->getCar();
	if (condition_clause == NULL)
		cout << "Invalid expression.  If statement missing condition clause." << endl;
	else
		condition_clause->print(0, p);
	//cout << endl;

	//print then clause
	Node * then_clause = t->getCdr()->getCdr()->getCar();
	cout << indents(n, ' ');
	if (then_clause == NULL) {
		cout << "Invalid expression.  If statement missing then clause." << endl;
	} else {
		then_clause->print(n + 2, p);
		//cout << endl;

		//print else clause
		Node * else_clause = t->getCdr()->getCdr()->getCdr()->getCar();
		cout << indents(n, ' ');
		if (else_clause != NULL) {
			else_clause->print(n + 2, p);
			//cout << endl;
		}
	}
	cout << indents(n, ' ');
	cout << ')' << endl;
}

void Let::print(Node * t, int n, bool p)
{
	cout << "(let" << endl;
	Node * cdr = t->getCdr();
	if (!cdr->isNull())
		cdr->print(n, p);
}

void Cond::print(Node * t, int n, bool p)
{
	cout << "(cond" << endl;
	Node * cdr = t->getCdr();
	if (!cdr->isNull())
		cdr->print(n, p);
}

void Define::print(Node * t, int n, bool p)
{
	cout << "(define ";
	Node * second_element = t->getCdr()->getCar();
	if (second_element->isPair())
		second_element->print(n, p);
	else
		second_element->print(0, p);
	cout << endl;
	Node * third_cons = t->getCdr()->getCdr();
	if (third_cons->isPair())
		third_cons->print(n, TRUE);
	else
		cout << "Invalid expression";
}

void Set::print(Node * t, int n, bool p)
{
	cout << "(set!";
	t->getCdr()->print(n, TRUE);
}

void Regular::print(Node * t, int n, bool p)
{
	Node * car = t->getCar();
	Node * cdr = t->getCdr();

	if (p) {
		cout << '(';
		if (!car->isNull()) {
			car->print(0, FALSE);
			if (t->isPair() && !car->isPair() && !cdr->isPair() && !cdr->isNull())
				cout << " .";
		}
		if (!cdr->isNull())
			cdr->print(1, FALSE);
		cout << ")";
	} else {
		if (!car->isNull()) {
			car->print(n, FALSE);
			if (t->isPair() && !car->isPair() && !cdr->isPair() && !cdr->isNull())
				cout << " .";
		}
		if (!cdr->isNull())
			cdr->print(1, FALSE);
	}
}

