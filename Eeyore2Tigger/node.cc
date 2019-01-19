#include "node.h"

#include <deque>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <deque>
#include <stack>

#include "output.h"

using namespace std;

Node::Node(NodeType nodeType_):nodeType(nodeType_){
    children = vector<Node*>();
};

NodeType Node::getNodeType(){
    return nodeType;
}
void Node::addChild(Node* child){
    children.push_back(child);
}

void Node::genCode(){};
void Node::printCode(){};

RootNode::RootNode():Node(RootNodeType){};

// 调用全局声明和函数的genCode
void RootNode::genCode(){
    stack<Node*> dfsStack = stack(Node*)();
    int l = children.size();
    for(int i = l-1;i>=0;i--){
        dfsStack.push(children[i]);
    }
    while(!dfsStack.empty()){
        Node* top = dfsStack.top();
        dfsStack.pop();
        if(top->getNodeType()==GlobalDeclareNodeType)
            top->genCode();
        else if(top->getNodeType()==FuncNodeType)
            top->genCode();
        else if(top->getNodeType()==OtherNodeType){
            int l = top->children.size();
            for(int i = l-1;i>=0;i--){
                dfsStack.push(top->children[i]);
            }   
        }
    }
}

// 调用全局声明和函数的printCode
void RootNode::printCode(){
    stack<Node*> dfsStack = stack(Node*)();
    int l = children.size();
    for(int i = l-1;i>=0;i--){
        dfsStack.push(children[i]);
    }
    while(!dfsStack.empty()){
        Node* top = dfsStack.top();
        dfsStack.pop();
        if(top->getNodeType()==GlobalDeclareNodeType)
            top->printCode();
        else if(top->getNodeType()==FuncNodeType)
            top->printCode();
        else if(top->getNodeType()==OtherNodeType){
            int l = top->children.size();
            for(int i = l-1;i>=0;i--){
                dfsStack.push(top->children[i]);
            }   
        }
    }
}

// 实时更新为已声明的全局变量表
IdManager GlobalDeclareNode::globalIdManager = IdManager();

// 同时将id作为孩子和更新globalIdManager
GlobalDeclareNode::GlobalDeclareNode(IdNode* id):Node(GlobalDeclareNodeType){
    addChild(id);
    globalIdManager.addId(id);
}

// 生成全局声明代码
void GlobalDeclareNode::genCode(){
    IdNode* child = (IdNode*)children[0];
    if(child->isArray())
        code = child->getTiggerName() + " = malloc "
         + to_string(child->getLength()) + "\n";
    else
        code = child->getTiggerName() + " = 0\n"; 
}

// 打印全局声明代码
void GlobalDeclareNode::printCode(){
    out << code;
}
// 用名字和参数个数初始化函数节点，同时注册函数的参数到idManager和regManager
FuncNode::FuncNode(const string& name_,int paraNum_):Node(FuncNodeType){
    name = name_;
    paraNum = paraNum_;
    regManager = RegManager();
    idManager = GlobalDeclareNode::globalIdManager;
    initPara();
}
// 按参数个数注册参数到idManager和regManager
void FuncNode::initPara(){
    vector<IdNode*> params = vector<IdNode*>();
    for(int i=0;i<paraNum;i++){
        string name = "p" + to_string(i);
        IdNode* para_i = new IdNode(name, false);
        idManager.addId(para_i);
        params.push_back(para_i);
    }
    regManager.initPara(params);

}
// 将子树中所有ExprNode调整为直接孩子，设置ExprNode的FuncParent
void FuncNode::adjustExprsToDirectChild(){
    vector<Node*> newChildren = vector<Node*>();
    stack<Node*> dfsStack = stack(Node*)();
    int l = children.size();
    for(int i = l-1;i>=0;i--){
        dfsStack.push(children[i]);
    }
    while(!dfsStack.empty()){
        Node* top = dfsStack.top();
        dfsStack.pop();
        if(top->getNodeType()==ExprNodeType)
            newChildren.push_back(top);
        else if(top->getNodeType()==OtherNodeType){
            int l = top->children.size();
            for(int i = l-1;i>=0;i--){
                dfsStack.push(top->children[i]);
            }   
        }
    }
    children = newChildren;
    for(auto& child:children){
        assert(child->getNodeType()==ExprNodeType);
        ((ExprNode*)child)->setFuncParent(this);
    }
}
// 从1开始为所有孩子ExprNode标号
void FuncNode::setExprsLineNo(){
    int lineNo = 1;
    for(auto& child:children){
        assert(child->getNodeType()==ExprNodeType);
        ((ExprNode*)child)->setLineNo(lineNo);
        lineNo++;
    }
}
// 将孩子中所有的IdNode指针指向idManager中的条目
// 调用 addIdToManagerIfNotExisted
// LocalDeclaration的孩子是第一次出现将会被加入idManager
// 遇到的Int常量在其它表达式中出现也会被不重复地加入idManager
void FuncNode::buildIdManager(){
    for(auto& child:children){
        for(auto& grandson:child->children){
            if(grandson->getNodeType()==IdNodeType)
                addIdToManagerIfNotExisted((IdNode*)grandson);
        }
    }
}
// 在idManager中查找id
// 已存在则返回对应条目指针，不存在则新建条目返回指针
IdNode* FuncNode::addIdToManagerIfNotExisted(IdNode* id){
    IdNode* ret = idManager.findId(id);
    if(ret!=NULL)
        return ret;
    else 
        ret = idManager.addId(id);
    return ret;
}

// 计算每个孩子Expr的活跃变量
// 调用calSuccForExprs和calAliveVarsForExprs
void FuncNode::analyzeLiveness(){
    calSuccForExprs();
    calAliveVarsForExprs();
}

// 为所有孩子ExprNode计算后继表达式集
void FuncNode::calSuccForExprs(){
    for(int i = 0;i<children.size();i++){
        ExprNode* child = (ExprNode*)children[i];
        ExprType childType = child->getExprType();
        if(childType==IfBranchType){
            if(i!=children.size()-1){
                ExprNode* nextChild = (ExprNode*)children[i+1];
                child->addSuccExpr(nextChild);
            }
            string label = child->getLabel();
            ExprNode* jumpToNode = searchLabel(label);
            child->addSuccExpr(jumpToNode);
        }
        else if(childType==GotoType){
            string label = child->getLabel();
            ExprNode* jumpToNode = searchLabel(label);
            child->addSuccExpr(jumpToNode);      
        }
        else{
            if(i!=children.size()-1){
                ExprNode* nextChild = (ExprNode*)children[i+1];
                child->addSuccExpr(nextChild);
            }
        }
    }
}
// 查找children中以label为标签,ExprType==LabelType的ExprNode
ExprNode* FuncNode::searchLabel(const string& labelToSearch){
    for(auto& child:children){
        string label;
        if(((ExprNode*)child)->getExprType()==LabelType)
        label = ((ExprNode*)child)->getLabel();
        if(label==labelToSearch)
            return (ExprNode*)child;
    }
    assert(false);
    return NULL;
}
// 迭代地从后向前扫描更新每个Expr的活跃变量集
void FuncNode::calAliveVarsForExprs(){
    bool hasChanged = false;
    while(true){
        for(auto it = children.rbegin();it!=children.rend();++it){
            ExprNode* child = (ExprNode*)(*it);

            // newSet = (join - left) U right
            set<IdNode*> oldAliveVarSet = child->getAliveVarSet();
            set<IdNode*> joinAliveVarSet = child->getJoinAliveVarSet();
            set<IdNode*> leftValueVarSet = child->getLeftValueVarSet();
            set<IdNode*> rightValueVarSet = child->getRightValueVarSet();
            
            set<IdNode*> tmp;
            set<IdNode*> newAliveVarSet;
            set_difference(oldAliveVarSet.begin(), oldAliveVarSet.end(), 
            leftValueVarSet.begin(), leftValueVarSet.end(),tmp);
            set_union(tmp.begin(),tmp.end(),rightValueVarSet.begin(), 
            rightValueVarSet.end(), newAliveVarSet);

            child->setAliveVarSet(newAliveVarSet);

            if(!hasChanged){
                hasChanged = !equal(newAliveVarSet.begin(), newAliveVarSet.end(), 
                oldAliveVarSet.begin(), oldAliveVarSet.end());
            }
        }
        if(!hasChanged) break;
    }
}

// 生成代码入口
void FuncNode::genCode(){
    adjustExprsToDirectChild();
    setExprsLineNo();
    buildIdManager();
    analyzeLiveness();
    for(auto& child:children)
        ((ExprNode*)child)->genCode();
}
// 打印代码入口
void FuncNode::printCode(){
    out << name + " [" + to_string(paraNum) << "] ["
     << to_string(regManager.getMemSize()) << "]" << endl; 
    for(auto& child:children){
        child->printCode();
    }
    out << "end " << name << endl;
}
ExprNode::ExprNode(ExprType exprType_, string op_, string label_ = string()):Node(ExprNodeType){
    exprType = exprType_;
    op = op_;
    label = label_;
    init();
}
void ExprNode::init(){
    lineNo = 0;
    funcParent = NULL;
    succExprSet = set<ExprNode*>();
    aliveVarSet = set<IdNode*>();
    code = string();
}
ExprType ExprNode::getExprType(){
    return exprType;
}
// 返回GotoType, IfBrachType, LabelType, callType的label,不带冒号
string ExprNode::getLabel(){
    assert(exprType==GotoType||exprType==IfBranchType
    ||exprType==LabelType||exprType==CallType);
    return label;
}
void ExprNode::setFuncParent(FuncNode* parent){
    funcParent = parent;
}
void ExprNode::setLineNo(int lineNo_){
    lineNo = lineNo_;
}
// 将succ添加入后继表达式集合succExprs
void ExprNode::addSuccExpr(ExprNode* succ){
    succExprSet.insert(succ);
}

set<IdNode*> ExprNode::getAliveVarSet(){
    return aliveVarSet;
}
void ExprNode::setAliveVarSet(const set<IdNode*>& newSet){
    aliveVarSet = newSet;   
}

// 得到JOIN(v) = Union[succExprs.aliveVars]
set<IdNode*> ExprNode::getJoinAliveVarSet(){
    set<IdNode*> joinSet;
    for(auto& succExpr:succExprSet){
        for(auto& aliveVar:succExpr->getAliveVarSet()){
            joinSet.insert(aliveVar);
        }
    }
    return joinSet;
}
// 得到作为右值的id集合
set<IdNode*> ExprNode::getRightValueVarSet(){
    set<IdNode*> rightValueSet = set<IdNode*>();
    if(exprType==Op2Type||exprType==VisitArrayType||exprType==IfBranchType){
        rightValueSet.insert(getRightValue1());
        rightValueSet.insert(getRightValue2());
    }
    else if(exprType==Op1Type||exprType==NoOpType||
    exprType==ReturnType){
        rightValueSet.insert(getRightValue());
    }
    else if(exprType==StoreArrayType){
        rightValueSet.insert(getVar());
        rightValueSet.insert(getRightValue1());
        rightValueSet.insert(getRightValue2());
    }
    else if(exprType==CallType){
        rightValueSet = getParas();
    }
    else ; // do no thing
    return rightValueSet;
}
// 得到作为左值的id集合
set<IdNode*> ExprNode::getLeftValueVarSet(){
    set<IdNode*> leftValueSet = set<IdNode*>();
    if(exprType==Op2Type||exprType==Op1Type||exprType==NoOpType||exprType==VisitArrayType||exprType==CallType||exprType==LocalDeclareType)
        leftValueSet.insert(getVar());
    return leftValueSet;
}
IdNode* ExprNode::getVar(){
    assert(exprType==Op2Type||exprType==Op1Type
     ||exprType==NoOpType||exprType==StoreArrayType||exprType==VisitArrayType||exprType==CallType||exprType==LocalDeclareType);
    return (IdNode*)children[0]; // 需要检查
}
IdNode* ExprNode::getRightValue(){
    assert(exprType==Op1Type||exprType==NoOpType||exprType==ReturnType)
    if(exprType==Op1Type||exprType==NoOpType)
        return (IdNode*)children[1];
    else //(exprType==ReturnType)
        return (IdNode*)children[0];
}
IdNode* ExprNode::getRightValue1(){
    assert(exprType==Op2Type||exprType==StoreArrayType||exprType==VisitArrayType||exprType==IfBranchType)
    if(exprType==Op2Type||exprType==StoreArrayType||exprType==VisitArrayType)
        return (IdNode*)children[1];
    else //(exprType==IfBranchType)
        return (IdNode*)children[0];
}   
IdNode* ExprNode::getRightValue2(){
    assert(exprType==Op2Type||exprType==StoreArrayType||exprType==VisitArrayType||exprType==IfBranchType)
    if(exprType==Op2Type||exprType==StoreArrayType||exprType==VisitArrayType)
        return (IdNode*)children[2];
    else //(exprType==IfBranchType)
        return (IdNode*)children[1];
}
// 得到CallFunc的所有参数节点，未完成
set<IdNode*> ExprNode::getParas(){
    int length = children.size();
    // 排除左值children[0]
    for(int i = 1;i<l;i++){

    }
}
void ExprNode::genCode(){

}
void ExprNode::printCode(){
    out << code;
}

// 一般变量的构造函数
IdNode::IdNode(string name_, bool isGlobal_ = false){
    name = name_;
    isGlobal = isGlobal_;
    isArray = false;
    isInteger = false;
    value = length = 0;
    funcParent = NULL;
}
// 数组的构造函数
IdNode::IdNode(string name_, bool isGlobal_, int length_){
    name = name_;
    isGlobal = isGlobal_;
    isArray = true;
    isInteger = false;
    length = length_;
    value = 0;
    funcParent = NULL;
}
// 整数的构造函数
IdNode::IdNode(int value_){
    name = string();
    isArray = isGlobal = false;
    isInteger = true;
    value = value_;
    length = 0;
    funcParent = NULL;
}
// 得到目标代码的全局变量名，将T改为v
string getTiggerName(){
    assert(isGlobal);
    string tiggerName = name;
    tiggerName[0] = 'v';
    return tiggerName;
}
int getLength(){
    assert(isArray);
    return length;
}
int getValue(){
    assert(isInteger);
    return value;
}
bool isArray(){
    return isArray;
}
bool isGlobal(){
    return isGlobal;
}
bool isInteger(){
    return isInteger;
}
void setFuncParent(FuncNode* funcParent){
    funcParent = funcParent;
}
bool IdNode::operator==(const IdNode& another){
    if(isInteger&&another.isInteger)
        return value==another.value;
    else
        return name==another.name;
    return false;
}
