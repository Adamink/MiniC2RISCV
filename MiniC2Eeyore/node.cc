#include "node.h"
#include "util.h"
using namespace std;

/*-----------------------------------------------
 * class Node
 *-----------------------------------------------*/
Node::Node(NodeType t_):nodeType(t_){
    codeBefore = stringstream();
    codeMiddle = stringstream();
    codeAfter = stringstream();
    children = vector<Node*>();
};
void Node::addChild(Node* child){
    children.push_back(child);
}
void Node::appendCode(string code){
    appendCodeBefore(code);
}
void Node::appendCodeBefore(string code){
    codeBefore << code;
}
void Node::appendCodeMiddle(string code){
    codeMiddle << code;
}
void Node::appendCodeAfter(string code){
    codeAfter << code;
}
void Node::printCodeRecursively(){
    print(codeBefore.str());
    if(children.size()>0){
        children[0]->printCodeRecursively();
    }
    print(codeMiddle.str());
    int l = children.size();
    for(int i = 1;i<l;i++){
        children[i]->printCodeRecursively();
    }
    print(codeAfter.str());
}
/*-----------------------------------------------
 * class RootNode
 *-----------------------------------------------*/
RootNode::RootNode():Node(RootNodeType){};
void RootNode::finishParsing(){
    printCodeRecursively();
}
/*-----------------------------------------------
 * class OtherNode
 *-----------------------------------------------*/
OtherNode::OtherNode():Node(OtherNodeType){};

/*-----------------------------------------------
 * class EmptyNode
 *-----------------------------------------------*/
EmptyNode::EmptyNode():Node(EmptyNodeType){};

/*-----------------------------------------------
 * class StatementNode
 *-----------------------------------------------*/
StatementNode::StatementNode():Node(StatementNodeType){};

/*-----------------------------------------------
 * class ParaNode
 *-----------------------------------------------*/
ParaNode::ParaNode(string name, IdType t):Node(ParaNodeType),idType(t),idName(name){};
ParaNode::ParaNode(IdType t):Node(ParaNodeType),idType(t){};
/*-----------------------------------------------
 * class ParaListNode
 *-----------------------------------------------*/
ParaListNode::ParaListNode():Node(ParaListNodeType){};

/*-----------------------------------------------
 * class FuncNode
 *-----------------------------------------------*/
FuncNode::FuncNode():Node(FuncNodeType){};

/*-----------------------------------------------
 * class ExprNode
 *-----------------------------------------------*/
ExprNode::ExprNode():Node(ExprNodeType){};

/*-----------------------------------------------
 * class ExprListNode
 *-----------------------------------------------*/
ExprListNode::ExprListNode():Node(ExprListNodeType){};
