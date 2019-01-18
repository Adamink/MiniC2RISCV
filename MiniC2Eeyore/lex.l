%{
#include "util.h"
#define YY_USER_ACTION update_loc();
%option noyywrap
%option yylineno

%x COMMENT
int     -?{[0-9]+}+
id      [a-zA-Z_][a-zA-Z0-9_]*
blank    ([ \f\r\t\v]+)*

%%
"//".*\n        {readToken(yytext);}
"/*"            {readToken(yytext);BEGIN(COMMENT);}
<COMMENT>"*/"   {readToken(yytext);BEGIN(INITIAL);}
<COMMENT>\n     {readToken(yytext);}
<COMMENT>.      {readToken(yytext);}
"int"           {readToken(yytext);return(TYPE);}
"\n"            {readToken(yytext);}
"++"            {readToken(yytext);return(DOUBLEPLUS);}
"--"            {readToken(yytext);return(DOUBLEMINUS);}
"+"             {readToken(yytext);return(PLUS);}
"-"             {readToken(yytext);return(MINUS);}
"*"             {readToken(yytext);return(TIME);}
"/"             {readToken(yytext);return(DIVIDE);}
"%"             {readToken(yytext);return(MOD);}
"!"             {readToken(yytext);return(NOT);}   
"&&"            {readToken(yytext);return(AND);}
"||"            {readToken(yytext);return(OR);}
"<"             {readToken(yytext);return(LESS);}
">"             {readToken(yytext);return(GREATER);}
"=="            {readToken(yytext);return(EQUAL);}
"!="            {readToken(yytext);return(NOTEQUAL);}
"="             {readToken(yytext);return(ASSIGN);}
"if"            {readToken(yytext);return(IF);}
"else"          {readToken(yytext);return(ELSE)}
"while"         {readToken(yytext);return(WHILE);}
"return"        {readToken(yytext);return(RETURN);}
"("             {readToken(yytext);return('(');}
")"             {readToken(yytext);return(')');}
"["             {readToken(yytext);return('[');}
"]"             {readToken(yytext);return(']');}
"{"             {readToken(yytext);return('{');}
"}"             {readToken(yytext);return('}');}
";"             {readToken(yytext);return(';');}
","             {readToken(yytext);return(',');}
{blank}         {readToken(yytext);}
{id}            {readToken(yytext);yylval.sval = strdup(yytext);return(ID);}
{int}           {readToken(yytext);yylval.ival = (int)atoi(yytext);return(INTEGER);}
.               {readToken(yytext);}
%%