#ifndef UTIL_H
#define UTIL_H

#include "parse.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*-----------------------------------------------
 * lex & parse
 *-----------------------------------------------*/
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(const char*);
extern FILE* yyin;
extern char* yytext;
extern void update_loc();
/*-----------------------------------------------
 * util
 *-----------------------------------------------*/
extern string linesFromSource[];
extern void setInput(char* fileName);
extern void readToken(char*);

extern int error;
extern int warning;
extern int debug;

extern stringstream outputStream;
extern stringstream errorStream;
extern stringstream warningStream;
extern stringstream debugStream;

extern string indicateLine(int l);
extern string separateLine(string msg);

extern void print(string);
extern void printErrorInfo(string, YYLTYPE);
extern void printWarningInfo(string, YYLTYPE);
extern void debugging(string);
extern void printFinal();
#endif