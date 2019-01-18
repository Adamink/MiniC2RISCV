#ifndef ENV_H
#define ENV_H
#include "parse.h"
#include "node.h"
#include <string>
#include <vector>
using namespace std;

/*-----------------------------------------------
 * global env
 *-----------------------------------------------*/
extern string inputFileName;
extern string funcName;
extern bool inFunc();

/*-----------------------------------------------
 * scope management
 *-----------------------------------------------*/
extern class Scope{
    public:
        int counter;
        int currentScope;
        Scope();
        vector<int> aliveScope();
        bool isScopeAlive(int);
        void newScope();
        void endScope();
}
extern Scope scope;
extern void newScope();
extern void endScope();
extern bool isScopeAlive();

/*-----------------------------------------------
 * func management
 *-----------------------------------------------*/
extern class FuncEntry{
    public:
        string funcName;
        FuncType funcType;
        vector<IdEntry> paraList;
        /* FuncEntry to init when decl and defn */
        FuncEntry(string,FuncType, ParaListNode*);
        /* FuncEntry to compare when called */
        FuncEntry(string, ExprListNode*);
}
extern int cmpFuncParaNum(FuncEntry& a, FuncEntry& b);
extern bool isFuncParaSame(FuncEntry& a, FuncEntry& b);
extern vector<FuncEntry> funcTable;
extern void createFuncEntry(string, FuncType, ParaListNode*, YYLTYPE);
extern FuncEntry* findFuncEntry(string name, YYLTYPE locate);

/*-----------------------------------------------
 * id management
 *-----------------------------------------------*/
extern int idCounter;
extern string newId();

extern class IdEntry{
    public:
    string CName,EName;
    IdType idType;
    int scope;
    IdEntry(string, string, IdType,int);
};

extern vector<IdEntry> idTable;
extern void createIdEntry(string, IdType,YYLTYPE);
extern void insertParaEntry(IdNode id);
extern string getIdName(string, YYLTYPE locate);

/*-----------------------------------------------
 * temp management
 *-----------------------------------------------*/
extern int tempCounter;
extern string newTemp();

/*-----------------------------------------------
 * label management
 *-----------------------------------------------*/
extern int labelCounter;
extern string newLabel();
#endif