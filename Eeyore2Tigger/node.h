#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <set>

#include "manager.h"

using namespace std;

enum NodeType{RootNodeType, GlobalDeclareNodeType, FuncNodeType, ExprNodeType, OtherNodeType, EmptyNodeType, IdNodeType, BlockNodeType};
enum ExprType{Op2Type, Op1Type, NoOpType, StoreArrayType, VisitArrayType, 
IfBranchType, GotoType, LabelType, CallType, ReturnType,LocalDeclareType};

class Node{
    protected:
        NodeType nodeType;
    public:
        vector<Node*> children;

        Node(NodeType nodeType_);
        NodeType getNodeType();
        vector<Node*> getChildren();
        void addChild(Node* child);
        virtual void genCode();
        virtual void printCode();
};
class OtherNode:public Node{
    public:
    OtherNode();
};
class RootNode:public Node{
    private:
    public:
        RootNode();
        // 调用全局声明和函数的genCode
        virtual void genCode();
        // 调用全局声明和函数的printCode
        virtual void printCode();
};
class GlobalDeclareNode:public Node{
    private:
        string code;
    public:
        // 实时更新为已声明的全局变量表
        static Manager globalManager;

        // 同时将id作为孩子和更新globalManager
        GlobalDeclareNode(IdNode* id);

        // 生成全局声明代码
        virtual void genCode();
        // 打印全局声明代码
        virtual void printCode();
};
class FuncNode:public Node{
    private:
        string name;
        int paraNum;
        Manager manager;

        // 按参数个数注册参数到manager,构造函数调用
        void initManager(Manager& globalManager);

        // 将子树中所有ExprNode调整为直接孩子，设置ExprNode的FuncParent
        void adjustExprsToDirectChild();

        // 从1开始为所有孩子ExprNode标号
        void setExprsLineNo();

        // 将孩子中所有的IdNode指针指向idManager中的条目
        // 调用 addIdToManagerIfNotExisted
        // LocalDeclaration的孩子是第一次出现将会被加入idManager
        // 遇到的Int常量在其它表达式中出现也会被不重复地加入idManager
        void buildIdManager();

        // 在全局变量的基础上将在idManager中查找id
        // 已存在则返回对应条目指针，不存在则新建条目返回指针
        IdNode* addIdToManagerIfNotExisted(IdNode* id);

        // 查找children中以label为标签,ExprType==LabelType的ExprNode
        ExprNode* searchLabel(const string& label);

        // 构建Blocks，将Expr孩子分配给Blocks, 并将Blocks作为孩子并分配id
        void buildBlocks();

        // 返回构建Blocks需要的leader集合
        set<int> calcLeaders();

    public:
        // 用名字和参数个数初始化函数节点，同时注册函数的参数到idManager和regManager
        FuncNode(const string& name_, int paraNum);

        // 生成代码入口，供RootNode调用
        virtual void genCode();

        // 打印代码入口，供RootNode调用
        virtual void printCode();

        Manager& getManager();
        int getParaNum();

};
class BlockNode:public Node{
    private:
        FuncNode* funcParent;
        int blockId;
        // 计算每个孩子Expr的活性变量集合
        void analyzeLiveness();
        
        // 设置孩子Expr的后继表达式集合
        void setSuccForExprs();

        // 计算Exit时的活性变量集合，是所有在该Block内定值的全局变量，非临时变量，函数参数的集合
        set<IdNode*> lastAliveVarSet;
        void calcLastAliveVarSet();

        // 计算每个孩子的活性变量集合
        void calcEveryAliveVarSet();

        // 设置孩子的兄弟节点
        void setChildBrotherhood();

    public:
        BlockNode(int id, FuncNode* parent);

        virtual void addChild(Node*);

        // 生成代码入口，供FuncNode调用，调用孩子Expr的genCode
        virtual void genCode();

        // 打印代码入口，供FuncNode调用，调用孩子Expr的genCode
        virtual void printCode();

        set<IdNode*> getLastAliveVarSet();
};
class ExprNode:public Node{
    private:
        ExprType exprType;
        int lineNo;
        FuncNode* funcParent;
        BlockNode* blockParent;
        ExprNode* next;
        set<ExprNode*> succExprSet; // 后继表达式集
        set<IdNode*> aliveVarSet;   // 活跃变量集
        //vector<IdNode*> paras;
        
        string code;
        string label;
        string op;

        void init();
        
        bool isLastInBlock();
        // 计算JOIN(v) = Union[succExprs.aliveVars]
        set<IdNode*> calcJoinAliveVarSet();
        // 计算作为右值的id集合
        set<IdNode*> calcRightValueVarSet();
        // 计算作为左值的id集合
        set<IdNode*> calcLeftValueVarSet();

    public:
        ExprNode(ExprType exprType_,string op_, string label_ = string());
        // 只为LabelType使用
        ExprNode(string label_);
        
        void setFuncParent(FuncNode* parent);
        void setBlockParent(BlockNode* parent);
        void setNext(ExprNode* next);
        void setLineNo(int lineNo_);

        // 将succ添加入后继表达式集合succExpr
        void addSuccExpr(ExprNode* succ);
        
        // 根据 AliveVarSet = (JOIN(V) - left) + right 计算活跃变量集
        void calcAliveVarSet();

        ExprType getExprType();
        int getLineNo();
        int getParaNum();
        // 返回GotoType, IfBrachType, LabelType的label,不带冒号
        string getLabel();
        string getOp();
        set<IdNode*> getAliveVarSet();
        vector<IdNode*> getParas();
        set<IdNode*> getLeftValueVarSet();
        IdNode* getVar();
        IdNode* getRightValue();
        IdNode* getRightValue1();
        IdNode* getRightValue2();

        // 判断id是否活跃
        bool isAlive(IdNode* );
        // 判断id是否之后就不再活跃了
        bool isAliveNext(IdNode* );

        // 生成代码存储到code
        virtual void genCode();

        // 打印代码到标准输出
        virtual void printCode();
};
class IdNode:public Node{
    private:
        string name;
        bool ifArray;
        bool ifGlobal;
        bool ifInteger;
        bool ifPara;
        bool ifTemp;
        bool ifCalleeSave;
        int value;
        int length;
        FuncNode* funcParent;
    public:
        // 一般变量的构造函数
        IdNode(string name_, bool isGlobal_ = false);
        // 数组的构造函数
        IdNode(string name_, bool isGlobal_, int length_);
        // 整数的构造函数
        IdNode(int value_);
        //　CalleeSave寄存器对应的idNode的构造函数
        IdNode(int locate, bool isCalleeSave);
        // 得到目标代码的全局变量名，将T改为v
        string getTiggerName();
        int getLength();
        int getValue();
        bool isArray();
        bool isGlobal();
        bool isLocal();
        bool isInteger();
        bool isPara();
        bool isCalleeSave();
        // 退出一个block时，全局非数组变量/函数参数/非临时非数组变量需要保存
        bool needSave();
        void setFuncParent(FuncNode* funcParent_);
        
        // 名字相同则相等，若为整数则值相同就相等
        friend bool operator==(const IdNode& here, const IdNode& another);

};

#endif