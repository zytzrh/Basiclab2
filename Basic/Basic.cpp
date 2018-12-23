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
#include "parsestatement.h"
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
		   program.removeParsedStatement(stringToInteger(beginword));
		   return;
	   }
	   string beginword2 = scanner.nextToken();
	   Statement *tmp;
	   if (beginword2 == "LET") {
		   tmp = parseLET(scanner);
	   }
	   else if (beginword2 == "PRINT") {
		   tmp = parsePRINT(scanner);
	   }
	   else if (beginword2 == "INPUT") {
		   tmp = parseINPUT(scanner);
	   }
	   else if (beginword2 == "END") {
		   tmp = parseEND(scanner);
	   }
	   else if (beginword2 == "GOTO") {
		   tmp = parseGOTO(scanner);
	   }
	   else if (beginword2 == "IF") {
		   tmp = parseIF(scanner);
	   }
	   else if(beginword2 == "REM"){
		   tmp = parseREM(scanner);
	   }
	   else {
		   error("SYNTAX ERROR");
	   }
	   program.setParsedStatement(stringToInteger(beginword), tmp);
	   program.addSourceLine(stringToInteger(beginword), line);
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
		   Statement *tmp = parseLET(scanner);
		   tmp->execute(state);
	   }
	   else if (beginword == "PRINT") {
		   Statement *tmp = parsePRINT(scanner);
		   tmp->execute(state);
	   }
	   else if (beginword == "INPUT") {
		   Statement *tmp = parseINPUT(scanner);
		   tmp->execute(state);
	   }
	   else {
		   error("SYNTAX ERROR");
	   }
   }
}

