/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO: ’≈—ÔÃÏ]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */
EvalState state;
Program program;
int main() {
   while (true) {
      try {
         processLine(getLine(), program, state);
		} catch (ErrorException & ex) {
         cout  << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);

   string beginword = scanner.nextToken();
   if (beginword == "")return;
   TokenType type = scanner.getTokenType(beginword);
   if (type == NUMBER) {
	   if (!scanner.hasMoreTokens()) {
		   program.removeSourceLine(stringToInteger(beginword));
		   return;
	   }
	   string beginword2 = scanner.nextToken();
	   if (beginword2 == "LET") {
		   Expression *exp = parseExp(scanner);
		   if (exp->getType() != COMPOUND)
			   error("SYNTAX ERROR");
		   if (((CompoundExp *)exp)->getLHS()->getType() != IDENTIFIER || ((CompoundExp *)exp)->getOp() != "=" || ((CompoundExp *)exp)->getRHS()->hasequation() == true)
			   error("SYNTAX ERROR");
		   LET *tmp = new LET((CompoundExp*)exp);
		   program.setParsedStatement(stringToInteger(beginword), tmp);
		   program.addSourceLine(stringToInteger(beginword), line);
	   }
	   else if (beginword2 == "PRINT") {
		   Expression *exp = parseExp(scanner);
		   if (exp->hasequation())
			   error("SYNTAX ERROR");
		   PRINT *tmp = new PRINT(exp);
		   program.setParsedStatement(stringToInteger(beginword), tmp);
		   program.addSourceLine(stringToInteger(beginword), line);
	   }
	   else if (beginword2 == "INPUT") {
		   Expression *exp = parseExp(scanner);
		   if (exp->getType() != IDENTIFIER)
			   error("SYNTAX ERROR");
		   INPUT *tmp = new INPUT((IdentifierExp *)exp);
		   program.setParsedStatement(stringToInteger(beginword), tmp);
		   program.addSourceLine(stringToInteger(beginword), line);
	   }
	   else if (beginword2 == "END") {
		   if (scanner.hasMoreTokens())
			   error("SYNTAX ERROR");
		   END *tmp = new END;
		   program.setParsedStatement(stringToInteger(beginword), tmp);
		   program.addSourceLine(stringToInteger(beginword), line);
	   }
	   else if (beginword2 == "GOTO") {
		   Expression *exp = parseExp(scanner);
		   if (exp->getType() != CONSTANT)
			   error("SYNTAX ERROR");
		   GOTO *tmp = new GOTO((ConstantExp *)exp);
		   program.setParsedStatement(stringToInteger(beginword), tmp);
		   program.addSourceLine(stringToInteger(beginword), line);
	   }
	   else if (beginword2 == "IF") {
		   Expression *exp = parsecompound2(scanner);
		   if (exp->getType() != COMPOUND) 
			   error("SYNTAX ERROR");
		   if(!exp->hasequation() || ((CompoundExp*)exp)->getLHS()->hasequation() || ((CompoundExp*)exp)->getRHS()->hasequation() || !scanner.hasMoreTokens())
			   error("SYNTAX ERROR");
		   Expression *number = parseExp(scanner);
		   if (number->getType() != CONSTANT)
			   error("SYNTAX ERROR");
		   IF *tmp = new IF((CompoundExp*)exp, number->eval(state));
		   delete number;
		   program.setParsedStatement(stringToInteger(beginword), tmp);
		   program.addSourceLine(stringToInteger(beginword), line);
	   }
	   else if(beginword2 == "REM"){
		   REM *tmp = new REM;
		   program.setParsedStatement(stringToInteger(beginword), tmp);
		   program.addSourceLine(stringToInteger(beginword), line);
	   }
	   else {
		   error("SYNTAX ERROR");
	   }
   }
   else {
	   if (beginword == "RUN") {
		   program.run(state);
	   }
	   else if (beginword == "LIST") {
		   program.list();
	   }
	   else if (beginword == "CLEAR") {
		   program.clear();
		   state.clear();
	   }
	   else if (beginword == "QUIT") {
		   exit(0);
	   }
	   else if (beginword == "HELP") {
		   cout << "Yet another basic interpreter";
	   }
	   else if (beginword == "LET") {
		   Expression *exp = parseExp(scanner);
		   if (exp->getType() != COMPOUND)
			   error("SYNTAX ERROR");
		   if (((CompoundExp *)exp)->getLHS()->getType() != IDENTIFIER || ((CompoundExp *)exp)->getOp() != "=" || ((CompoundExp *)exp)->getRHS()->hasequation() == true)
			   error("SYNTAX ERROR");
		   LET *tmp = new LET((CompoundExp*)exp);
		   tmp->execute(state);
	   }
	   else if (beginword == "PRINT") {
		   Expression *exp = parseExp(scanner);
		   if (exp->hasequation())
			   error("SYNTAX ERROR");
		   PRINT *tmp = new PRINT(exp);
		   tmp->execute(state);
	   }
	   else if (beginword == "INPUT") {
		   Expression *exp = parseExp(scanner);
		   if (exp->getType() != IDENTIFIER)
			   error("SYNTAX ERROR");
		   INPUT *tmp = new INPUT((IdentifierExp *)exp);
		   tmp->execute(state);
	   }
	   else {
		   error("SYNTAX ERROR");
	   }
   }
   //scanner.saveToken(beginword);
   
}

