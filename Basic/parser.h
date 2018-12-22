/*
 * File: parser.h
 * --------------
 * This file acts as the interface to the parser module.
 */

#ifndef _parser_h
#define _parser_h

#include <string>
#include "exp.h"

#include "../StanfordCPPLib/tokenscanner.h"

/*
 * Function: parseExp
 * Usage: Expression *exp = parseExp(scanner);
 * -------------------------------------------
 * Parses an expression by reading tokens from the scanner, which must
 * be provided by the client.  The scanner should be set to ignore
 * whitespace and to scan numbers.
 */

Expression *parseExp(TokenScanner & scanner);

/*
 * Function: readE
 * Usage: Expression *exp = readE(scanner, prec);
 * ----------------------------------------------
 * Returns the next expression from the scanner involving only operators
 * whose precedence is at least prec.  The prec argument is optional and
 * defaults to 0, which means that the function reads the entire expression.
 */

Expression *readE(TokenScanner & scanner, int prec = 0);

/*用于扫描if a ( < or = or > ) b中的a且留下运算符在scanner中*/
Expression *parsecompound1(TokenScanner & scanner);

/*用于扫描if a ( < or = or > ) b中的b不留下THEN在scanner中*/
Expression *parsecompound2(TokenScanner & scanner);

/*
 * Function: readT
 * Usage: Expression *exp = readT(scanner);
 * ----------------------------------------
 * Returns the next individual term, which is either a constant, an
 * identifier, or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner);

/*
 * Function: precedence
 * Usage: int prec = precedence(token);
 * ------------------------------------
 * Returns the precedence of the specified operator token.  If the token
 * is not an operator, precedence returns 0.
 */

int precedence(std::string token);

#endif
