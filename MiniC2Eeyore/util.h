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
extern void yyerror(char*);
extern FILE* yyin;
extern char* yytext;
extern void update_loc();
/*-----------------------------------------------
 * util
 *-----------------------------------------------*/
extern string linesFromSource[];
extern void setInput(char* fileName);
extern void readToken(char*);

extern int debug;
extern int error;
extern stringstream outputStream;
extern stringstream debugStream;
extern stringstream errorStream;
extern void print(string);
extern void printDebugInfo(string, YYLTYPE);
extern void printError(string);

extern void print
#endif