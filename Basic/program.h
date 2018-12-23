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

	/*加入某行的string*/

   void addSourceLine(int lineNumber, std::string line);

    /*移除某行的string*/

   void removeSourceLine(int lineNumber);

	/*加入某行的parsed represention*/

   void setParsedStatement(int lineNumber, Statement *stmt);

	/*移除某行的parsed represention*/

   void removeParsedStatement(int lineNumber);

    /*运行program*/
   
   void run(EvalState & state);

    /*找到某行并进入*/

   void findAndGoto(int lineNumber);

	/*进入下一行*/

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
