#ifndef _parsestatement_h
#define _parsestatement_h
/*�������������ת��Ϊstatementָ��ĺ���*/
Statement *parseLET(TokenScanner & scanner);

Statement *parsePRINT(TokenScanner & scanner);

Statement *parseINPUT(TokenScanner & scanner);

Statement *parseEND(TokenScanner & scanner);

Statement *parseGOTO(TokenScanner & scanner);

Statement *parseIF(TokenScanner & scanner);

Statement *parseREM(TokenScanner & scanner);
#endif