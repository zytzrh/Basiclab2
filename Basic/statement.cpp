/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "program.h"
#include "../StanfordCPPLib/simpio.h"
using namespace std;
extern Program program;
/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

/*LET*/

LET::LET(CompoundExp *tmp) {
	p = tmp;
}

void LET::execute(EvalState & state) {
	p->eval(state);
}

LET::~LET() {
	delete p;
}

StatementType LET::getType(){
	return Let;
}

/*PRINT*/

PRINT::PRINT(Expression *tmp) {
	p = tmp;
}

void PRINT::execute(EvalState & state) {
	cout << p->eval(state) << '\n';
}

PRINT::~PRINT() {
	delete p;
}

StatementType PRINT::getType() {
	return Print;
}

/*INPUT*/

INPUT::INPUT(IdentifierExp *tmp) {
	p = tmp;
}

void INPUT::execute(EvalState & state) {
	bool flag = false;//false代表未成功读入
	while (!flag) {
		flag = true;
		try {
			cout << " " << "?" << " ";
			string tmp = getLine();
			state.setValue(p->getName(), stringToInteger(tmp));
		}
		catch (ErrorException & ex) {
			cout << ex.getMessage() << endl;
			flag = false;
		}
	}
}

INPUT::~INPUT() {
	delete p;
}

StatementType INPUT::getType() {
	return Input;
}

/*END*/

void END::execute(EvalState & state) {}

StatementType END::getType() {
	return End;
}

/*GOTO*/

GOTO::GOTO(ConstantExp *tmp) {
	p = tmp;
}

void GOTO::execute(EvalState & state) {
	program.findAndGoto(p->eval(state));
}

GOTO::~GOTO() {
	delete p;
}

StatementType GOTO::getType() {
	return Goto;
}

/*IF*/

IF::IF(CompoundExp *tmp, int linetmp){
	p = tmp;
	objectline = linetmp;
}

void IF::execute(EvalState & state){
	if (p->getOp() == "=" && p->getLHS()->eval(state) == p->getRHS()->eval(state)) {
		program.findAndGoto(objectline);
	}
	else if (p->getOp() == ">" && p->getLHS()->eval(state) > p->getRHS()->eval(state)) {
		program.findAndGoto(objectline);
	}
	else if (p->getOp() == "<" && p->getLHS()->eval(state) < p->getRHS()->eval(state)) {
		program.findAndGoto(objectline);
	}
	else {
		program.gotonextline();
	}
}

IF::~IF(){
	delete p;
}

StatementType IF::getType(){
	return If;
}

/*REM*/

void REM::execute(EvalState & state){}

StatementType REM::getType()
{
	return Rem;
}

