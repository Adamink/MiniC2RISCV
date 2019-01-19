#include <iostream>
#include <cassert> 
#include <sstream>
#include <string>

#include "node.h"
using namespace std;
Node::Node(){
    codeBeforeChildren = string();
    codeAfterChildren = string();
    children = vector<Node*>();
    selfType = OtherType;
    stk = -1;
}
Node::Node(NodeType t){
    codeBeforeChildren = string();
    codeAfterChildren = string();
    children = vector<Node*>();
    selfType = t;
    stk = -1;
}
void Node::printAllCode(){
    cout << codeBeforeChildren;
    if(debug) cerr << codeBeforeChildren;
    for(auto& i:children){
        i->printAllCode();
    }
    cout << codeAfterChildren;
    if(debug) cerr << codeAfterChildren;
}
void Node::appendCode(const string& src){
    codeBeforeChildren+=src;
}
void Node::appendCodeBeforeChildren(const string& src){
    codeBeforeChildren+=src;
}
void Node::appendCodeAfterChildren(const string& src){
    codeAfterChildren+=src;
}
void Node::addChild(Node* child){
    children.push_back(child);
}
void Node::setStackSize(int size){
    assert(selfType==FuncType);
    stk = size;
}
void Node::fillReturnNode(){
    static int stkVisited = -1;
    if(selfType==ReturnType){
        stk = stkVisited;
        stringstream code;
        code << "\tlw\tra," << (stk - 4) << "(sp)" << endl;
        code << "\tadd\tsp,sp," << stk << endl;
        code << "\tjr\tra" << endl;
        appendCode(code.str());
        return;
    }
    if(selfType==FuncType){
        stkVisited = stk;
    }
    for(auto& i:children){
        i->fillReturnNode();
    }
}
