#include "env.h"

#include <stack>
using namespace std;

/*-----------------------------------------------
 * global env
 *-----------------------------------------------*/
string inputFileName = string();
string funcName = string();
bool inFunc(){
    return Scope.currentScope > 0;
}
/*-----------------------------------------------
 * scope management
 *-----------------------------------------------*/
Scope::Scope(){
    counter = 0;
    currentScope = 0;
    aliveScope = vector<int>();
    aliveScope.push_back(currentScope);
}
bool Scope::isScopeAlive(int x){
    for(auto& i:aliveScope)
        if(x==i)
            return true;
    return false;
}
void Scope::newScope(){
    counter++;
    currentScope = counter;
    aliveScope.push_back(currentScope);
}
void Scope::endScope(){
    currentScope = aliveScope.back();
    aliveScope.pop_back();
}
Scope scope = Scope();
void newScope(){
    score.newScope();
}
void endScope(){
    score.endScope();
}
bool isScopeAlive(int s){
    return score.isScopeAlive(s);
}

/*-----------------------------------------------
 * func management
 *-----------------------------------------------*/
FuncEntry::FuncEntry(string name, FuncType t, ParaListNode* p){
    funcName = name;
    funcType = t;
    int paraCounter = 0;
    // deep-first traverse node p to get all para in order
    // allocate para name and store in paraList
    if(p!NULL){
        stack<Node*> dfsStack = stack<Node*>();
        int l = p->children.size();
        for(int i = l-1;i>=0;i--)
            dfsStack.push(p->children[i]);
        while(!dfsStack.empty()){
            Node* top = dfsStack.top();
            dfsStack.pop();
            if(top->nodeType!=ParaNodeType){
                vector<Node*> topchildren = top->children();
                int l = topchildren.size();
                for(int i = l-1;i>=0;i--)
                    dfsStack.push(topchildren[i]);
            }
            else{
                ParaNode* para = (ParaNode*)top;
                EName = "p" + to_string(paraCounter);
                paraCounter++;
                IdEntry id = IdEntry(para->CName, EName,para->idType,scope.currentScope);
                paraList.push_back(id);    
            }
        }
    }
FuncEntry::FuncEntry(string name, ExprListNode* p){
    funcName = name;
    funcType = CallType;
    // same as above except for type of nodes
    if(p!=NULL){
        stack<Node*> dfsStack = stack<Node*>();
        int l = p->children.size();
        for(int i = l-1;i>=0;i--)
            dfsStack.push(p->children[i]);
        while(!dfsStack.empty()){
            Node* top = dfsStack.top();
            dfsStack.pop();
            if(top->nodeType!=ExprNodeType){
                vector<Node*> topchildren = top->children();
                int l = topchildren.size();
                for(int i = l-1;i>=0;i--)
                    dfsStack.push(topchildren[i]);
            }
            else{
                ExprNode* expr = (ExprNode*)top;
                IdEntry id = IdEntry("", expr->valueID, IntType,scope.currentScope);
                paraList.push_back(id);    
            }
        }
    }
}
}
int cmpFuncParaNum(FuncEntry& a, FuncEntry& b){
    return a.paraList.size() - b.paraList.size();
}
bool isFuncParaSame(FuncEntry& a, FuncEntry& b){
    int la = a.paraList.size();
    int lb = b.paraList.size();
    if(la!=lb) return false;
    for(int i = 0;i<la;i++){
        if(a.paraList[i].idType!=b.paraList[i].idType)
            return false;
    }
    return true;
}
vector<FuncEntry> funcTable = vector<FuncEntry>();
/*
 * check func's compatability with previous ones
 * if ok, insert funcEntry to funcTable for future check
 * if also FuncDefn insert paraList to idTable and newScope()
 */
void createFuncEntry(string name, FuncType t, ParaListNode* p, YYLTYPE locate){
    if(t==DefnType) {
        newScope();
        funcName = name;
    }
    FuncEntry func = FuncEntry(name, t, p);
    for(auto& it:funcTable){
        if(it.funcName==name&&!isFuncParaSame(func,it)){
            string errMsg = "conflicting types for '" + name + "'";
            printErrorInfo(errMsg, locate);
        }
        else if(it.funcName==name&&isFuncParaSame(func,it)&&t==DefnType&&it.funcType==DefnType){
            string errMsg = "redefinition of '" + name +"'";
            printErrorInfo(errMsg, locate);
        }
        else{
            funcTable.push_back(func);
            // insert para idEntry for future use
            if(t==DefnType){
                for(auto para:func.paraList){
                    insertParaEntry(para);
                }
            }
        }
    }
}

FuncEntry* findFuncEntry(string name, YYLTYPE locate){
    for(auto it = funcTable.begin();it!=funcTable.end();++it){
        if(it->funcName==name)
            return it;  // ?
    }
    // name not found
    string wrnMsg = "implicit declaration of function '" + name + "'";
    printWarningInfo(wrnMsg, locate);
    return NULL;
}
/*-----------------------------------------------
 * id management
 *-----------------------------------------------*/
int idCounter = 0;
string newId(){
    string id = "T" + to_string(idCounter);
    idCounter++;
    return id;
}

IdEntry::IdEntry(string CName_,string EName_, IdType_ idType_, int scope_):CName(CName_),EName(EName_),idType(idType_),scope(scope_){};
vector<IdEntry> idTable = vector<IdEntry>();
/* 
 * create a idEntry and insert to table
 * else printErrorInfo
 */
void createIdEntry(string CName, IdType t, YYLTYPE locate){
    for(auto it = idTable.rbegin();it!=idTable.rend();++it){
        if(it->CName==CName&&it->scope==scope.currentScope){
            // redefinition, stop creating
            string errMsg = "redefinition of '" + CName + "'";
            printErrorInfo(errMsg, locate);
            return;
        }
    }
    string EName = newId();
    IdType id = IdType(CName, EName, t, scope.currentScope);
    idTable.push_back(id);
}
void insertParaEntry(IdNode id){
    idTable.push_back(id);
}
/* 
 * return EName of a CName
 * if not found, return an empty string and printErrorInfo
 */
string getIdName(string CName, YYLTYPE locate){
    for(auto it = idTable.rbegin();it!=idTable.rend();++it){
        if(it->CName==CName&&isScopeAlive(it->scope)){
            return = it->EName;
            break;
        }
    }
    // not found
    string errMsg ="'" + CName + "' was not declared in this scope";
    printErrorInfo(errMsg, locate);
    return string();
}
/*-----------------------------------------------
 * temp management
 *-----------------------------------------------*/
int tempCounter = 0;
string newTemp(){
    string temp = "t" + to_string(tempCounter);
    tempCounter++；
    return temp;
}

/*-----------------------------------------------
 * label management
 *-----------------------------------------------*/
int labelCounter = 0;
string newLabel(){
    string label = "l" + to_string(labelCounter);
    labelCounter++;
    return label;
}