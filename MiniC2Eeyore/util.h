#ifndef UTIL_H
#define UTIL_H

#include "parse.h"
#include <iostream>
#include <string>
using namespace std;

/*-----------------------------------------------
 * lex & parse
 *-----------------------------------------------*/
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(char*);
extern FILE* yyin;
/*-----------------------------------------------
 * util
 *-----------------------------------------------*/
extern string linesFromSource[];
extern void setInput(char* fileName);
extern void readToken(char*);

extern int debug;
extern void printDebugInfo(string);
extern void print(string);
extern void printError(string);
#endif