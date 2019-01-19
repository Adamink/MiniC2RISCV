#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <set>

#include "idmanager.h"
#include "regmanager.h"

using namespace std;

enum NodeType{RootNodeType, GlobalDeclareNodeType, FuncNodeType, ExprNodeType, OtherNodeType, EmptyNodeType, IdNodeType};
enum ExprType{Op2Type, Op1Type, NoOpType, StoreArrayType, VisitArrayType, 
IfBranchType, GotoType, LabelType, CallType, ReturnType,LocalDeclareType};

class Node{
    protected:
        NodeType nodeType;
    public:
        vector<Node*> children;

        Node(NodeType nodeType_);
        NodeType getNodeType();
        vector<Node*>* getChildren();
        void addChild(Node* child);
        virtual void genCode();
        virtual void printCode();
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
        static IdManager globalIdManager;

        // 同时将id作为孩子和更新globalIdManager
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
        // 管理内存和寄存器
        RegManager regManager;

        // 初始化为当前的globalIdManager
        IdManager idManager;

        // 按参数个数注册参数到idManager和regManager
        void initPara();

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

        // 计算每个孩子Expr的活跃变量
        // 调用calSuccForExprs和calAliveVarsForExprs
        void analyzeLiveness();

        // 为所有孩子ExprNode计算后继表达式集
        void calSuccForExprs();
        
        // 查找children中以label为标签,ExprType==LabelType的ExprNode
        ExprNode* searchLabel(const string& label);

        // 迭代地从后向前扫描更新每个Expr的活跃变量集
        void calAliveVarsForExprs();

    public:
        // 用名字和参数个数初始化函数节点，同时注册函数的参数到idManager和regManager
        FuncNode(const string& name_, int paraNum);

        // 生成代码入口
        virtual void genCode();

        // 打印代码入口
        virtual void printCode();

};
class ExprNode:public Node{
    private:
        ExprType exprType;
        int lineNo;
        FuncNode* funcParent;
        // 后继表达式集
        set<ExprNode*> succExprSet;
        // 活跃变量集
        set<IdNode*> aliveVarSet;
        string code;
        string label;
        string op;
        void init();

        IdNode* getVar();
        IdNode* getRightValue();
        IdNode* getRightValue1();
        IdNode* getRightValue2();
        // 只被CallType使用
        set<IdNOde*> getParas();
        // 得到存储左值的寄存器
        void getReg();
        
    public:
        ExprNode(ExprType exprType_,string op_, string label_ = string());
        // 只为LabelType使用
        ExprNode(string label_);
        ExprType getExprType();

        // 返回GotoType, IfBrachType, LabelType的label,不带冒号
        string getLabel();
        void setFuncParent(FuncNode* parent);
        void setLineNo(int lineNo_);

        // 将succ添加入后继表达式集合succExprs
        void addSuccExpr(ExprNode* succ);

        set<IdNode*> getAliveVarSet();
        void setAliveVarSet(const set<IdNode*>& newSet);
        // 得到JOIN(v) = Union[succExprs.aliveVars]
        set<IdNode*> getJoinAliveVarSet();
        // 得到作为右值的id集合
        set<IdNode*> getRightValueVarSet();
        // 得到作为左值的id集合
        set<IdNode*> getLeftValueVarSet();

        // 生成代码存储到code
        virtual void genCode();

        // 打印代码到标准输出
        virtual void printCode();

};
class IdNode:public Node{
    private:
        string name;
        bool isArray;
        bool isGlobal;
        bool isInteger;
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

        // 得到目标代码的全局变量名，将T改为v
        string getTiggerName();
        int getLength();
        int getValue();
        bool isArray();
        bool isGlobal();
        bool isInteger();
        void setFuncParent(FuncNode* funcParent_);
        
        // 名字相同则相等，若为整数则值相同就相等
        bool operator==(const IdNode& another);

};

#endif