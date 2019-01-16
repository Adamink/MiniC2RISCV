#include "util.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
/*-----------------------------------------------
 * util
 *-----------------------------------------------*/

static int maxLines = 1024;
string linesFromSource[maxLines];
/* copy input to file and set linesFromSource */
void setInput(char* fileName){
    fstream f = fstream(fileName);
    string line;
    int i = 0;
    while(getline(cin, line)){
        linesFromSource[i] = line;
        f << line;
    }
    fstream.close();
}

/* read a new token and remember a line */
void readToken(char* s){
    printDebugInfo(string(s));
}

int debug = 1;
void printDebugInfo(string s){
    if(debug)
        cerr << s;        
}

void print(string s){
    cout << s;
}
void printError(string s){
    cerr << s;
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