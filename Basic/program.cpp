/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
#include <map>
using namespace std;

Program::Program() {}

Program::~Program() {
	clear();
}

void Program::clear() {
	for (iterstate = statementtable.begin(); iterstate != statementtable.end(); iterstate++) {
		delete iterstate->second;
   }
	statementtable.clear();
	stringtable.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
	removeSourceLine(lineNumber);
	stringtable[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber) {
	iterstringtablle = stringtable.find(lineNumber);
	if (iterstringtablle != stringtable.end())	stringtable.erase(iterstringtablle);
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
	removeParsedStatement(lineNumber);
	statementtable[lineNumber] = stmt;
}

void Program::removeParsedStatement(int lineNumber)
{	
	iterstate = statementtable.find(lineNumber);
	if (iterstate != statementtable.end()) {
		delete iterstate->second;
		statementtable.erase(iterstate);
	}
}


void Program::findAndGoto(int lineNumber) {
	iterstate = statementtable.find(lineNumber);
	if (iterstate == statementtable.end())
		error("LINE NUMBER ERROR");
}

void Program::gotonextline()
{
	iterstate++;
}

void Program::list()
{
	for (iterstringtablle = stringtable.begin(); iterstringtablle != stringtable.end(); iterstringtablle++) {
		cout << iterstringtablle->second << "\n";
	}
}

void Program::run(EvalState & state) {
	for (iterstate = statementtable.begin(); iterstate != statementtable.end();) {
		if (iterstate->second->getType() == End) {
			iterstate->second->execute(state);
			break;
		}
		else if (iterstate->second->getType() == Goto || iterstate->second->getType() == If) {
			iterstate->second->execute(state);
			continue;
		}
		else {
			iterstate->second->execute(state);
			iterstate++;
		}
	}
}
