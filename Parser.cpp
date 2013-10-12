// Parser.cpp -- the implementation of class Parser

#include "Parser.h"

Node * Parser::parseExp()
{
	// TODO: write code for parsing an exp
	return parseExp(scanner->getNextToken());
}

Node * Parser::parseRest()
{
	// TODO: write code for parsing rest
	return parseRest(scanner->getNextToken());
}

Node * Parser::parseExp(Token * token)
{
	switch (token->getType()) {
		case LPAREN:
			return parseRest();
			break;
		case TRUET:
			return Parser::getTrueNode();
			break;
		case FALSET:
			return Parser::getFalseNode();
			break;
		case QUOTE:
			return new Cons(new Ident("quote"), new Cons(parseExp(), Parser::getNilNode()));
			break;
		case INT:
			return new IntLit(token->getIntVal());
			break;
		case STRING:
			return new StrLit(token->getStrVal());
			break;
		case IDENT:
			return new Ident(token->getName());
			break;
		default:
			cout << "Something broke in parseExp\n";
			return NULL;
	}
}

Node * Parser::parseRest(Token * token)
{
	switch (token->getType()) {
		case RPAREN:
			return Parser::getNilNode();
		case DOT:
			return parseDot();
		default:
			return new Cons(parseExp(token), parseRest());
	}
}

Node * Parser::parseDot()
{
	Node * dotExp = parseExp();
	Token * token = scanner->getNextToken();
	if (token->getType() != RPAREN)
		cout << "missing right parenthesis after expression\n";
	while (token->getType() != RPAREN) {
		Token * nextToken = scanner->getNextToken();
	}
	return dotExp;
}

//singleton methods
Node * Parser::getNilNode()
{
	if (nilNode == NULL)
		nilNode = new Nil();
	return nilNode;
}

Node * Parser::getTrueNode()
{
	if (trueNode == NULL)
		trueNode = new BoolLit(true);
	return trueNode;
}

Node * Parser::getFalseNode()
{
	if (falseNode == NULL)
		falseNode = new BoolLit(false);
	return falseNode;
}
