/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

enum StatementType { Let, Print, Input, End, If, Goto, Rem};

class Statement {

public:
/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

	Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

   virtual StatementType getType() = 0;
};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */


class LET : public Statement {
private:
	CompoundExp *p;
public:
	LET(CompoundExp *tmp);
	virtual void execute(EvalState & state);
	virtual ~LET();
	virtual StatementType getType();
};
/*PRINT*/
class PRINT : public Statement {
private:
	Expression *p;
public:
	PRINT(Expression *tmp);
	virtual void execute(EvalState & state);//PRINT a = 6Ô¤¾¯
	virtual ~PRINT();
	virtual StatementType getType();
};
/*INPUT*/
class INPUT : public Statement {
private:
	IdentifierExp *p;
public:
	INPUT(IdentifierExp *tmp);
	virtual void execute(EvalState & state);
	virtual ~INPUT();
	virtual StatementType getType();
};
/*END*/
class END : public Statement {
public:
	virtual void execute(EvalState & state);
	virtual StatementType getType();
};
/*GOTO*/
class GOTO : public Statement {
private:
	ConstantExp *p;
public:
	GOTO(ConstantExp *tmp);
	virtual void execute(EvalState & state);
	virtual ~GOTO();
	virtual StatementType getType();
};
/*IF*/
class IF : public Statement{
private:
	CompoundExp *p;
	int objectline;
public:
	IF(CompoundExp *tmp, int linetmp);
	virtual void execute(EvalState & state);
	virtual ~IF();
	virtual StatementType getType();
};

class REM : public Statement {
public:
	virtual void execute(EvalState & state);
	virtual StatementType getType();
};
#endif
