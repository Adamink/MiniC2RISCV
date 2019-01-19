#ifndef NODE_H
#define NODE_H
#include "type.h"
#include <vector>
#include <string>
#include <sstream>
using namespace std;
class Node{        
    public:
        NodeType nodeType;
        vector<Node*> children;
        stringstream codeBefore;
        stringstream codeMiddle;
        stringstream codeAfter;
        Node(NodeType t_);
        void addChild(Node*);
        void appendCode(string);
        void appendCodeBefore(string);
        void appendCodeMiddle(string);
        void appendCodeAfter(string);
        void printCodeRecursively();
};
class RootNode:public Node{
    public:
        RootNode();
        void finishParsing();
};
class OtherNode:public Node{
    public:
        OtherNode();
};
class EmptyNode:public Node{
    public:
        EmptyNode();
};
class StatementNode:public Node{
    public:
        StatementNode();
};
class ParaNode:public Node{
    public:
        ParaNode(string, IdType);
        ParaNode(IdType);
        IdType idType;
        string idName;
};
class ParaListNode:public Node{
    public:
        ParaListNode();
};
class FuncNode:public Node{
    public:
        FuncNode();
};
class ExprNode:public Node{
    public:
        bool isInteger;
        bool isID;
        string valueID;
        ExprNode();
};
class ExprListNode:public Node{
    public:
        ExprListNode();
};
#endif