#include "util.h"
#include "env.h"
#include <cstdio>
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
static const int maxLines = 1024;
string linesFromSource[maxLines];
/* copy input to file and set linesFromSource */
void setInput(char* fileName){
    fstream f;
    f.open(fileName, fstream::in | fstream::out | fstream::trunc);
    string line;
    stringstream lineBuffer = stringstream();
    int i = 1;
    char c;
    while((c = getchar())!=EOF){
        if(c!='\t')
            lineBuffer << c;
        else
            lineBuffer << "    "; // replace '\t' with 4 spaces
        if(c=='\n'){
            linesFromSource[i] = lineBuffer.str();
            i++;
            f << lineBuffer.str();
            lineBuffer.clear();
        }
    }
    /*
    while(getline(cin, line)){
        linesFromSource[i] = line + "\n";
        i++;
        f << line << endl;
    }
    f.close();*/
}

/* read a new token and remember a line */
void readToken(char* s){
    debugging(string(s));
}


int error = 0;
int warning = 0;
int debug = 1;

stringstream outputStream = stringstream();
stringstream errorStream = stringstream();
stringstream warningStream = stringstream();
stringstream debugStream = stringstream();

string indicateLine(int l){
    stringstream line = stringstream();
    for(int i = 0;i<l-1;i++){
        line << " ";
    }
    line << "^" << endl;
    return line.str();
}

string separateLine(string msg){
    int beforeLen = 20;
    int dstLen = 60;
    int msgLen = msg.length() + 2;
    int afterLen = dstLen - beforeLen - msgLen;
    stringstream line = stringstream();
    line << endl;
    for(int i = 0;i<beforeLen;i++){
        line << "=";
    }
    line << " " << msg << " ";
    for(int i = 0;i<afterLen;i++){
        line << "=";
    }
    line << endl;
    return line.str();
}

void print(string s){
    outputStream << s;
}

void printErrorInfo(string errMsg, YYLTYPE l){
    error = 1;

    string locate = string();
    string line = string();
    string errInfo = string();
    string envMsg = string();
    string locateMsg = string();
    if(inFunc())
        envMsg = inputFileName + ": In function '" + funcName + "':\n"; 

    locate = to_string(l.first_line) + ":" + to_string(l.first_column) + ":";
    errMsg = inputFileName + ":" + locate + " error: " + errMsg + "\n";
    line = linesFromSource[l.first_line];
    locateMsg = indicateLine(l.first_column);
    errInfo = envMsg + errMsg + line + locateMsg;
    errorStream << errInfo;      
}
void printWarningInfo(string wrnMsg, YYLTYPE l){
    warning = 1;

    string locate = string();
    string line = string();
    string wrnInfo = string();
    string envMsg = string();
    string locateMsg = string();
    if(inFunc())
        envMsg = inputFileName + ": In function '" + funcName + "':\n"; 

    locate = to_string(l.first_line) + ":" + to_string(l.first_column) + ":";
    wrnMsg = inputFileName + ":" + locate + " warning: " + wrnMsg + "\n";
    line = linesFromSource[l.first_line];
    locateMsg = indicateLine(l.first_column);
    wrnInfo = envMsg + wrnMsg + line + locateMsg;
    warningStream << wrnInfo;
}
void debugging(string s){
    cerr << s;
}

void printFinal(){
    if(error){
        cerr << separateLine("Error Info");
        cerr << errorStream.str();
    }
    else{
        cerr << separateLine("Warning Info");
        cerr << warningStream.str();
        cerr << separateLine("Output");
        cout << outputStream.str();
    }

}
/*-----------------------------------------------
 * main
 *-----------------------------------------------*/
int main(int argc, char *argv[]){
    char fileName[20] = "eeyore.log";
    setInput(fileName);
    yyin = fopen(fileName,"r");
    cerr << separateLine("Debugging Info");
    yyparse();
    printFinal();
}