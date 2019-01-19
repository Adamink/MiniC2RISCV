%{
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <string.h>

int lineCount = 0;
int debug = 1;
void redirectInput(){
    if(debug)
        cerr << yytext;
}
%}
digit   [0-9]
int     {digit}+
id      [a-zA-Z_][a-zA-Z0-9_]*
blank    ([ \f\r\t\v]+)*
%%
"//".*\n    {redirectInput();lineCount++;}
"\n"    {redirectInput();lineCount++;}
"+"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "+");           return(PLUS);}
"-"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "-");           return(MINUS);}
"*"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "*"); return(TIME);}
"/"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "/"); return(DIVIDE);}
"%"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "%"); return(MOD);}
"!"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "!");return(NOT); }   
"&&"    {redirectInput();yylval.sval = new char[3]; strcpy(yylval.sval, "&&"); return(AND);}
"||"    {redirectInput();yylval.sval = new char[3]; strcpy(yylval.sval, "||"); return(OR);}
"<"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "<"); return(LESS);}
">"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, ">"); return(GREATER);}
"=="    {redirectInput();yylval.sval = new char[3]; strcpy(yylval.sval, "=="); return(EQUAL);}
"!="    {redirectInput();yylval.sval = new char[3]; strcpy(yylval.sval, "!="); return(NOTEQUAL);}
"="     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "="); return(ASSIGN);}
"["     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "["); return(LBRAC);}
"]"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, "]"); return(RBRAC);}
":"     {redirectInput();yylval.sval = new char[2]; strcpy(yylval.sval, ":"); return(COLON);}
"if"    {redirectInput();yylval.sval = new char[3]; strcpy(yylval.sval, "if"); return(IF);}
"goto"  {redirectInput();yylval.sval = new char[5]; strcpy(yylval.sval, "goto"); return(GOTO);}
"call"  {redirectInput();yylval.sval = new char[5]; strcpy(yylval.sval, "call"); return(CALL);}
"param" {redirectInput();yylval.sval = new char[6]; strcpy(yylval.sval, "param"); return(PARAM);}
"end"   {redirectInput();yylval.sval = new char[4]; strcpy(yylval.sval, "end"); return(END);}
"f_"{id}    {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, yytext); return(FUNC);}
"return"    {redirectInput();yylval.sval = new char[7]; strcpy(yylval.sval, "return"); return(RETURN);}
"var"       {redirectInput();yylval.sval = new char[4]; strcpy(yylval.sval, "var"); return(VAR);}
"l"{int}    {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, yytext); return(LABEL);}
{blank}     {redirectInput();/* no return */}
{id}        {redirectInput();yylval.sval = new char[20]; strcpy(yylval.sval, yytext); return(ID);}
{int}       {redirectInput();yylval.ival = (int)atoi(yytext);return(INTEGER);}
%%