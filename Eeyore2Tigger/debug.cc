#include "debug.h"

#include <iostream>

using namespace std;

map<int, string> nodeTypeMap = {
    {0,"Root"},
    {1,"GlobalDeclare"},
    {2,"FuncNode"},
    {3,"ExprNode"},
    {4,"OtherNode"},
    {5,"EmptyNode"},
    {6,"IdNode"},
    {7,"BlockNode"}
};
map<int,string> exprTypeMap = {
    {0,"Op2"},
    {1,"Op1"},
    {2,"NoOp"},
    {3,"StoreArray"},
    {4,"VisitArray"},
    {5,"IfBranch"},
    {6,"Goto"},
    {7,"Label"},
    {8,"Call"},
    {9,"Return"},
    {10,"LocalDeclare"}
};
void traverseNode(Node* p){
    if(p->getNodeType()==ExprNodeType)
        cerr << exprTypeMap[((ExprNode*)p)->getExprType()] << ":" << endl;
    else{
        cerr << nodeTypeMap[p->getNodeType()]<<":";
        for(auto& child:p->children){
            cerr << nodeTypeMap[child->getNodeType()] << " ";
        }
        cerr << endl;
    }
    for(auto& child:p->children)
        traverseNode(child);
    //cerr << p->getNodeType() << ":" << p->getChildren().size() << endl;

}
void printSet(set<int> s){
    for(auto& it:s)
        cerr << it << " ";
    cerr << endl;
}