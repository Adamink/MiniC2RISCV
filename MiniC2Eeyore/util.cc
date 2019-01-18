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


int debug = 0;
int error = 0;

void print(string s){
    outputStream << s;
}

void printDebugInfo(string errMsg, YYLTYPE l){
    debug = 1;

    string locate = string();
    string line = string();
    string debugInfo = string();

    if(inFunc())
        envMsg = inputFileName + ": In function '" + funcName + "':\n"; 

    locate = to_string(l.first_line) + ":" + to_string(l.first_column) + ":";
    errMsg = inputFileName + ":" + locate + " error: " + errMsg + "\n";
    line = linesFromSource[l.first_line];

    debugInfo = envMsg + errMsg + line;
    debugStream << debugInfo;      
}

void printError(string s){
    errorStream << s;
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