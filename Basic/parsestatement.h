#ifndef _parsestatement_h
#define _parsestatement_h
/*将各个类型语句转化为statement指针的函数*/
Statement *parseLET(TokenScanner & scanner);

Statement *parsePRINT(TokenScanner & scanner);

Statement *parseINPUT(TokenScanner & scanner);

Statement *parseEND(TokenScanner & scanner);

Statement *parseGOTO(TokenScanner & scanner);

Statement *parseIF(TokenScanner & scanner);

Statement *parseREM(TokenScanner & scanner);
#endif