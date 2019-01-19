# Tigger 文档
## 代码优化
1. 基本块划分
2. 流图构造
3. 得到块内每个表达式的变量活跃性和后续信息
4. 得到每个块的DAG
5. 生成优化代码
## 寄存器分配
1. 按函数分块
2. 迭代计算块内每个表达式的变量活性区间
3. 一边朴素分配寄存器一边生成代码
4. 窥孔优化
## UML
```cpp
enum NodeType{};
class Node{
    private:
    NodeType nodeType;
    vector<Node*> child;
    public:
    Node(NodeType nodeType_);
    void addChild(Node* child);
};
class RootNode:public Node{
    private:
    public:
    RootNode();
};
class FuncNode:public Node{
    private:
    string name;
    RegManager regManager;
    IdManager idManager;
    void calSuccForExprs();
    void calAliveVarsForExprs();
    public:
    FuncNode(string name_);

    // 将子树中所有ExprNode调整为直接孩子
    void adjustExprsToDirectChild();

    // 从1开始为所有孩子ExprNode标号
    void setExprsLineNo();

    // 调用calSuccForExprs和calAliveVarsForExprs
    // 计算每个孩子Expr的活跃变量
    void analyzeLiveness();

};
class ExprNode:public Node{
    private:
    ExprType exprType;
    int lineNo;
    set<IdNode*> aliveVars;
    set<ExprNode*> succExprs;
    public:
        // 得到JOIN(v) = Union[succExprs.aliveVars]
        set<IdNode*> getJoinAliveVars();
        setAliveVars()
};
class IdNode:public Node{
    private:
    string name;
    bool isArray;
    bool isGlobal;
    int length;
    Node* funcParent;
    public:
    IdNode(string name_, isGlobal = false, isArray = false);
    IdNode(string name_, isGlobal, isArray, int length);
    string getName();
    bool isArray();
    bool isGlobal();
    operator==
}

```