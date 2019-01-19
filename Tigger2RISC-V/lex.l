%{
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

int lineCount = 0;
int debug = 1;
void redirectInput(){
    if(debug)
        inputFile << yytext;
}
%}
digit   [0-9]
int     -?{digit}+
id      [a-zA-Z_][a-zA-Z0-9_]*
blank    ([ \f\r\t\v]+)*
%%
"//".*\n    {redirectInput();lineCount++;}
"\n"    {redirectInput();lineCount++;}
"+"     {redirectInput();yylval.ival = PLUS;return(PLUS);}
"-"     {redirectInput();yylval.ival = MINUS;return(MINUS);}
"*"     {redirectInput();yylval.ival = TIME;return(TIME);}
"/"     {redirectInput();yylval.ival = DIVIDE;return(DIVIDE);}
"%"     {redirectInput();yylval.ival = MOD;return(MOD);}
"!"     {redirectInput();yylval.ival = NOT;return(NOT); }   
"&&"    {redirectInput();yylval.ival = AND;return(AND);}
"||"    {redirectInput();yylval.ival = OR;return(OR);}
"<"     {redirectInput();yylval.ival = LESS;return(LESS);}
">"     {redirectInput();yylval.ival = GREATER;return(GREATER);}
"=="    {redirectInput();yylval.ival = EQUAL;return(EQUAL);}
"!="    {redirectInput();yylval.ival = NOTEQUAL;return(NOTEQUAL);}
"="     {redirectInput();yylval.ival = ASSIGN;return(ASSIGN);}
"["     {redirectInput();yylval.ival = LBRAC;return(LBRAC);}
"]"     {redirectInput();yylval.ival = RBRAC;return(RBRAC);}
":"     {redirectInput();yylval.ival = COLON;return(COLON);}
"if"    {redirectInput();yylval.ival = IF;return(IF);}
"goto"  {redirectInput();yylval.ival = GOTO;return(GOTO);}
"call"  {redirectInput();yylval.ival = CALL;return(CALL);}
"end"   {redirectInput();yylval.ival = END;return(END);}
"store" {redirectInput();yylval.ival = STORE;return(STORE);}
"loadaddr"  {redirectInput();yylval.ival = LOADADDR;return(LOADADDR);}
"load"  {redirectInput();yylval.ival = LOAD;return(LOAD);}
"malloc"    {redirectInput();yylval.ival = MALLOC;return(MALLOC);}
"f_"{id}    {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, yytext+2); return(FUNC);}
"return"    {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, "return"); return(RETURN);}
"l"{int}    {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, yytext); return(LABEL);}
"x"{int}|"a"{int}|"s"{int}|"t"{int} {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, yytext); return(REG);}
{blank}     {redirectInput();/* no return */}
{id}        {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, yytext); return(VARIABLE);}
{int}       {redirectInput();yylval.ival = (int)atoi(yytext);return(INTEGER);}
%%