#ifndef UTIL_H
#define UTIL_H

#include "parse.h"
#include <string>
using namespace std;

/*-----------------------------------------------
 * lex & parse
 *-----------------------------------------------*/
extern int yylex(void);
extern int yyparse(void);
extern void yyerror(char*);

extern void readToken(char*);


/*-----------------------------------------------
 * util
 *-----------------------------------------------*/
extern int debug;
extern void debugPrint(string);
#endif