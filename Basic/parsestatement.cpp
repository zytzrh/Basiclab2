#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "parsestatement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
extern EvalState state;
Statement * parseLET(TokenScanner & scanner)
{
	Expression *exp = parseExp(scanner);
	if (exp->getType() != COMPOUND)
		error("SYNTAX ERROR");
	if (((CompoundExp *)exp)->getLHS()->getType() != IDENTIFIER || ((CompoundExp *)exp)->getOp() != "=" || ((CompoundExp *)exp)->getRHS()->hasequation() == true)
		error("SYNTAX ERROR");
	return new LET((CompoundExp*)exp);
}

Statement * parsePRINT(TokenScanner & scanner)
{
	Expression *exp = parseExp(scanner);
	if (exp->hasequation())
		error("SYNTAX ERROR");
	return new PRINT(exp);
}

Statement * parseINPUT(TokenScanner & scanner)
{
	Expression *exp = parseExp(scanner);
	if (exp->getType() != IDENTIFIER)
		error("SYNTAX ERROR");
	return new INPUT((IdentifierExp *)exp);
}

Statement * parseEND(TokenScanner & scanner)
{
	if (scanner.hasMoreTokens())
		error("SYNTAX ERROR");
	return new END;
}

Statement * parseGOTO(TokenScanner & scanner)
{
	Expression *exp = parseExp(scanner);
	if (exp->getType() != CONSTANT)
		error("SYNTAX ERROR");
	return new GOTO((ConstantExp *)exp);
}

Statement * parseIF(TokenScanner & scanner)
{
	Expression *exp = parsecompound2(scanner);
	if (exp->getType() != COMPOUND)
		error("SYNTAX ERROR");
	if (!exp->hasequation() || ((CompoundExp*)exp)->getLHS()->hasequation() || ((CompoundExp*)exp)->getRHS()->hasequation() || !scanner.hasMoreTokens())
		error("SYNTAX ERROR");
	Expression *number = parseExp(scanner);
	if (number->getType() != CONSTANT)
		error("SYNTAX ERROR");
	IF *tmp = new IF((CompoundExp*)exp, number->eval(state));
	delete number;
	return tmp;
}

Statement * parseREM(TokenScanner & scanner)
{
	return new REM;
}
