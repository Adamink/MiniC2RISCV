#include "util.h"
#include "env.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
/*-----------------------------------------------
 * lex & parse
 *-----------------------------------------------*/
void update_loc(){
    static int curr_line = 1;
    static int curr_col  = 1;

    yylloc.first_line   = curr_line;
    yylloc.first_column = curr_col;

    {char * s; for(s = yytext; *s != '\0'; s++){
    if(*s == '\n'){
        curr_line++;
        curr_col = 1;
    }else{
        curr_col++;
    }
    }}

    yylloc.last_line   = curr_line;
    yylloc.last_column = curr_col-1;
}
/*-----------------------------------------------
 * util
 *-----------------------------------------------*/
static int maxLines = 1024;
string linesFromSource[maxLines];
/* copy input to file and set linesFromSource */
void setInput(char* fileName){
    fstream f = fstream(fileName);
    string line;
    int i = 1;
    while(getline(cin, line)){
        linesFromSource[i] = line;
        f << line;
    }
    fstream.close();
}

/* read a new token and remember a line */
void readToken(char* s){
    printError(string(s));
}


int error = 0;
int warning = 0;
int debug = 0;

stringstream outputStream = stringstream();
stringstream errorStream = stringstream();
stringstream warningStream = stringstream();
stringstream debugStream = stringstream();

void print(string s){
    outputStream << s;
}

void printErrorInfo(string errMsg, YYLTYPE l){
    error = 1;

    string locate = string();
    string line = string();
    string errInfo = string();

    if(inFunc())
        envMsg = inputFileName + ": In function '" + funcName + "':\n"; 

    locate = to_string(l.first_line) + ":" + to_string(l.first_column) + ":";
    errMsg = inputFileName + ":" + locate + " error: " + errMsg + "\n";
    line = linesFromSource[l.first_line];

    errInfo = envMsg + errMsg + line;
    errorStream << errInfo;      
}
void printWarningInfo(string wrnMsg, YYLTYPE l){
    warning = 1;

    string locate = string();
    string line = string();
    string warningInfo = string();

    if(inFunc())
        envMsg = inputFileName + ": In function '" + funcName + "':\n"; 

    locate = to_string(l.first_line) + ":" + to_string(l.first_column) + ":";
    wrnMsg = inputFileName + ":" + locate + " warning: " + wrnMsg + "\n";
    line = linesFromSource[l.first_line];

    wrnInfo = envMsg + wrnMsg + line;
    warningStream << wrnInfo;
}
void debugging(string s){
    debugStream << s;
}
/*-----------------------------------------------
 * main
 *-----------------------------------------------*/
int main(int argc, char *argv[]){
    char fileName[20] = "file.log";
    setInput(fileName);
    yyin = open(fileName,"r");
    yyparse();
}