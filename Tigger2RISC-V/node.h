#ifndef NODE_H
#define NODE_H
#include <string>
#include <cstring>
#include <vector>

using namespace std;
enum NodeType{FuncType, ReturnType, EmptyType, OtherType};
class Node{
    private:
    string codeBeforeChildren;
    string codeAfterChildren;
    vector<Node*> children;
    NodeType selfType;
    // field only for functype
    int stk;
    public:
    Node();
    Node(NodeType);
    void printAllCode();
    void appendCode(const string& src);
    void appendCodeBeforeChildren(const string& src);
    void appendCodeAfterChildren(const string& src);
    void addChild(Node* child);
    void setStackSize(int size);
    void fillReturnNode();
};
#endif