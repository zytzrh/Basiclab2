/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC
 * program.
 */

#ifndef _program_h
#define _program_h

#include <string>
#include <map>
#include "statement.h"
using namespace std;

class Program {
public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

   Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

   ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

   void clear();

	/*����ĳ�е�string*/

   void addSourceLine(int lineNumber, std::string line);

    /*�Ƴ�ĳ�е�string*/

   void removeSourceLine(int lineNumber);

	/*����ĳ�е�parsed represention*/

   void setParsedStatement(int lineNumber, Statement *stmt);

	/*�Ƴ�ĳ�е�parsed represention*/

   void removeParsedStatement(int lineNumber);

    /*����program*/
   
   void run(EvalState & state);

    /*�ҵ�ĳ�в�����*/

   void findAndGoto(int lineNumber);

	/*������һ��*/

   void gotonextline();
  
	/*list*/
   void list();

private:
	int linenow;
	map<int, Statement *> statementtable;
	map<int, string> stringtable;
	map<int, Statement *>::iterator iterstate;
	map<int, string>::iterator iterstringtablle;

};

#endif
