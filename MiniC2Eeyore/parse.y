%{
#include "util.h"
#include "node.h"
#include <string>
using namespace std;
#define YYERROR_VERBOSE 1
%}
/* generate include-file with symbols and types */
%defines
%locations

/* a more advanced semantic type */
%union {
    int ival;
    char* sval;
    Node* nval;
}
%token <ival> TYPE INTEGER PLUS MINUS TIME DIVIDE MOD NOT AND OR LESS GREATER EQUAL NOTEQUAL ASSIGN IF ELSE WHILE RETURN MAIN DOUBLEPLUS DOUBLEMINUS
%token <sval> '(' ')' '[' ']' '{' '}' ';' ',' ID
%type <nval> VarDefn FuncDefn FuncDecl Statement Statements MainFunc Program ParaList VarDecl Expression Block GlobalList ExprList 

%nonassoc IF
%nonassoc ELSE
%right RETURN
%right ASSIGN
%left OR
%left AND
%left EQUAL NOTEQUAL
%left LESS GREATER
%left PLUS MINUS
%left TIME DIVIDE MOD
%right NOT UMINUS DOUBLEPLUS DOUBLEMINUS

%start Program
%%
Program:    GlobalList
    {
        
    }
    ;

%%
void yyerror(char *s) {
    printError(s);
}