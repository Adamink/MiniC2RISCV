#include "node.h"

#include <deque>
#include <cassert>
#include <algorithm>
#include <iostream>
#include <stack>
#include "output.h"
#include "debug.h"
using namespace std;

/* ------------------ Node ------------------ */
Node::Node(NodeType nodeType_):nodeType(nodeType_){
    children = vector<Node*>();
};
NodeType Node::getNodeType(){
    return nodeType;
}
vector<Node*> Node::getChildren(){
    return children;
}
void Node::addChild(Node* child){
    children.push_back(child);
}
void Node::genCode(){};
void Node::printCode(){};

/* ------------------ OtherNode ------------------ */
OtherNode::OtherNode():Node(OtherNodeType){};

/* ------------------ RootNode ------------------ */
RootNode::RootNode():Node(RootNodeType){};

// 调用全局声明和函数的genCode
void RootNode::genCode(){
    cerr << "RootNode::genCode starts" << endl;
    vector<Node*> usefulChild = vector<Node*>();
    stack<Node*> dfsStack = stack<Node*>();
    int l = children.size();
    for(int i = l-1;i>=0;i--)
        dfsStack.push(children[i]);
    while(!dfsStack.empty()){
        Node* top = dfsStack.top();
        dfsStack.pop();
        if(top->getNodeType()==OtherNodeType){
            vector<Node*> topchildren = top->getChildren();
            int len = topchildren.size();
            for(int i = len-1;i>=0;i--)
                dfsStack.push(topchildren[i]);
        }
        else if(top->getNodeType()==GlobalDeclareNodeType)
            usefulChild.push_back(top);
        else if(top->getNodeType()==FuncNodeType)
            usefulChild.push_back(top);
    }        
    cerr << "RootNode::genCode finishes calculating useful children" << endl;
    for(auto& child:usefulChild)
        child->genCode();
    cerr << "RootNode::genCode ends" << endl;
}

// 调用全局声明和函数的printCode
void RootNode::printCode(){
    cerr << "RootNode::printCode starts" << endl;
    vector<Node*> usefulChild = vector<Node*>();

    stack<Node*> dfsStack = stack<Node*>();
    int l = children.size();
    for(int i = l-1;i>=0;i--)
        dfsStack.push(children[i]);
    while(!dfsStack.empty()){
        Node* top = dfsStack.top();
        dfsStack.pop();
        if(top->getNodeType()==OtherNodeType){
            vector<Node*> topchildren = top->getChildren();
            int len = topchildren.size();
            for(int i = len-1;i>=0;i--)
                dfsStack.push(topchildren[i]);
        }
        else if(top->getNodeType()==GlobalDeclareNodeType)
            usefulChild.push_back(top);
        else if(top->getNodeType()==FuncNodeType)
            usefulChild.push_back(top);
    }
    
    for(auto& child:usefulChild)
        child->printCode();
    cout << out.str();
    cerr << "RootNode::printCode ends" << endl;
}


/* ------------------ GlobalDeclareNode ------------------ */
// 实时更新为已声明的全局变量表
Manager GlobalDeclareNode::globalManager = Manager();

// 同时将id作为孩子和更新globalManager
GlobalDeclareNode::GlobalDeclareNode(IdNode* id):Node(GlobalDeclareNodeType){
    addChild(id);
    globalManager.addId(id);
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


/* ------------------ FuncNode ------------------ */
// 用名字和参数个数初始化函数节点，同时注册函数的参数到idManager和regManager
FuncNode::FuncNode(const string& name_,int paraNum_):Node(FuncNodeType){
    name = name_;
    paraNum = paraNum_;
    initManager(GlobalDeclareNode::globalManager);
}

// 按参数个数注册参数到manager,构造函数调用
void FuncNode::initManager(Manager& globalManager){
    manager = Manager(globalManager);
    vector<IdNode*> params = vector<IdNode*>();
    for(int i=0;i<paraNum;i++){
        string name = "p" + to_string(i);
        IdNode* para_i = new IdNode(name, false);
        params.push_back(para_i);
    }
    manager.setParams(params);
}

Manager& FuncNode::getManager(){
    return manager;
}

int FuncNode::getParaNum(){
    return paraNum;
}

// 生成代码入口，供RootNode调用
void FuncNode::genCode(){
    adjustExprsToDirectChild();
    setExprsLineNo();
    buildIdManager();
    buildBlocks();
    for(auto& child:children)
        ((BlockNode*)child)->genCode();
}

// 打印代码入口，供RootNode调用
void FuncNode::printCode(){
    out << name + " [" + to_string(paraNum) << "] ["
     << to_string(manager.getStackSize()) << "]" << endl; 
    for(auto& child:children){
        child->printCode();
    }
    out << "end " << name << endl;
}

// 将子树中所有ExprNode调整为直接孩子，设置ExprNode的FuncParent
void FuncNode::adjustExprsToDirectChild(){
    cerr << "FuncNode::adjustExprsToDirectChild starts" << endl;
    vector<Node*> newChildren = vector<Node*>();
    stack<Node*> dfsStack = stack<Node*>();
    int l = children.size();
    for(int i = l-1;i>=0;i--)
        dfsStack.push(children[i]);
    while(!dfsStack.empty()){
        Node* top = dfsStack.top();
        dfsStack.pop();
        if(top->getNodeType()==OtherNodeType){
            vector<Node*> topchildren = top->getChildren();
            int len = topchildren.size();
            for(int i = len-1;i>=0;i--)
                dfsStack.push(topchildren[i]);
        }
        else if(top->getNodeType()==ExprNodeType)
            newChildren.push_back(top);
        // else do nothing
    }
    children = newChildren;
    for(auto& child:children){
        assert(child->getNodeType()==ExprNodeType);
        ((ExprNode*)child)->setFuncParent(this);
    }
    cerr << "FuncNode::adjustExprsToDirectChild ends" << endl;
    traverseNode(this);
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

// 将孩子中所有的IdNode指针指向manager中的条目
// 调用 addIdToManagerIfNotExisted
// LocalDeclaration的孩子是第一次出现将会被加入idManager
// 遇到的Int常量在其它表达式中出现也会被不重复地加入idManager
void FuncNode::buildIdManager(){
    cerr << "FuncNode::buildIdManager starts" << endl;
    for(auto& child:children){
        for(auto& grandson:child->children){
            if(grandson->getNodeType()==IdNodeType)
                addIdToManagerIfNotExisted((IdNode*)grandson);
        }
    }
    cerr << "FuncNode::buildIdManager ends" << endl;
}

// 在idManager中查找id
// 已存在则返回对应条目指针，不存在则新建条目返回指针
IdNode* FuncNode::addIdToManagerIfNotExisted(IdNode* id){
    IdNode* ret = manager.findId(id);
    if(ret!=NULL)
        return ret;
    else 
        ret = manager.addId(id);
    return ret;
}

// 构建Blocks，将Expr孩子分配给Blocks, 并将Blocks作为孩子并分配id
void FuncNode::buildBlocks(){
    cerr << "FuncNode::buildBlocks starts" << endl;
    int blockId = 0;
    set<int> leaders;
    // leaders 是块的首表达式下标集合
    leaders = calcLeaders();
    set<int> workList = leaders;
    // printSet(workList);
    vector<Node*> blocks = vector<Node*>();
    int l = children.size();
    // 根据leaders分块
    while(!workList.empty()){
        blockId++;
        BlockNode* block = new BlockNode(blockId, this);
        int firstExpr = *(workList.begin());
        workList.erase(firstExpr);
        block->addChild(children[firstExpr-1]);
        for(int i = firstExpr + 1;i < l&&leaders.count(i)==0;i++)
            block->addChild(children[i-1]);
        blocks.push_back(block);
    }
    children = blocks;
    cerr << "FuncNode::buildBlocks ends" << endl;
    traverseNode(this);
}

// 返回构建Blocks需要的leader集合
set<int> FuncNode::calcLeaders(){
    set<int> leaders = set<int>();
    if(children.size()!=0)
        leaders.insert(1);
    int l = children.size();
    for(int i = 0;i<l;i++){
        ExprNode* expr = (ExprNode*) children[i];
        if(expr->getExprType()==GotoType){
            string label = expr->getLabel();
            ExprNode* dst = searchLabel(label);
            leaders.insert(dst->getLineNo());
        }
        else if(expr->getExprType()==IfBranchType){
            string label = expr->getLabel();
            ExprNode* dst = searchLabel(label);
            leaders.insert(dst->getLineNo());
            if(i!=l-1){
                ExprNode* next = (ExprNode*)children[i+1];
                leaders.insert(next->getLineNo());
            }
        }
    }
    return leaders;
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


/* ------------------ BlockNode ------------------ */
BlockNode::BlockNode(int id, FuncNode* parent):
 Node(BlockNodeType){
    blockId = id;
    funcParent = parent;
    lastAliveVarSet = set<IdNode*>();
};

void BlockNode::addChild(Node* child){
    Node::addChild(child);
    ((ExprNode*)child)->setBlockParent(this);
};

void BlockNode::genCode(){
    setChildBrotherhood();
    analyzeLiveness();
    for(auto& expr:children){
        expr->genCode();
    }
}  
void BlockNode::printCode(){
    for(auto& expr:children){
        expr->printCode();
    }
}

set<IdNode*> BlockNode::getLastAliveVarSet(){
    return lastAliveVarSet;
}

void BlockNode::setChildBrotherhood(){
    cerr << "BlockNode::setChildBrotherhood starts" << endl;
    ExprNode* last = NULL;
    int len = children.size();
    for(int i = len-1;i>=0;i--){
        ExprNode* expr = (ExprNode*)children[i];
        expr->setNext(last);
        last = expr;
    }
    cerr << "BlockNode::setChildBrotherhood ends" << endl;
}
// 计算每个孩子Expr的活性变量集合
void BlockNode::analyzeLiveness(){
    cerr << "BlockNode::analyzeLiveness starts" << endl;
    setSuccForExprs();
    calcLastAliveVarSet();
    calcEveryAliveVarSet();
    cerr << "BlockNode::analyzeLiveness ends" << endl;
}

// 设置孩子Expr的后继表达式集合
void BlockNode::setSuccForExprs(){
    int l = children.size();
    for(int i=0;i<l-1;i++){
        ((ExprNode*)children[i])->addSuccExpr((ExprNode*)children[i+1]);
    }
}
 // 计算Exit时的活性变量集合，是所有在该Block内定值的全局变量，非临时变量，函数参数的集合
void BlockNode::calcLastAliveVarSet(){
    for(auto& child:children){
        ExprNode* expr = (ExprNode*) child;
        set<IdNode*> candidates;
        candidates = expr->getLeftValueVarSet();
        for(auto& id:candidates){
            if(id->needSave())
                lastAliveVarSet.insert(id);
        }
    }
}

// 计算每个孩子的活性变量集合
void BlockNode::calcEveryAliveVarSet(){
    int l = children.size();
    for(int i = l-1;i>=0;i--){
        ExprNode* expr = (ExprNode*)children[i];
        expr->calcAliveVarSet();
    }
}



/* ------------------ ExprNode ------------------ */
ExprNode::ExprNode(ExprType exprType_, string op_, 
 string label_):Node(ExprNodeType){
    exprType = exprType_;
    op = op_;
    label = label_;
    init();
}
ExprNode::ExprNode(string label_):ExprNode(LabelType, "", label_){};
void ExprNode::init(){
    lineNo = 0;
    funcParent = NULL;
    blockParent = NULL;
    next = NULL;
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
string ExprNode::getOp(){
    assert(exprType==Op2Type||exprType==Op1Type||exprType==IfBranchType);
    return op;
}
void ExprNode::setFuncParent(FuncNode* parent){
    funcParent = parent;
}
void ExprNode::setBlockParent(BlockNode* parent){
    blockParent = parent;
}
void ExprNode::setNext(ExprNode* next_){
    next = next_;
}
void ExprNode::setLineNo(int lineNo_){
    lineNo = lineNo_;
}
int ExprNode::getLineNo(){
    return lineNo;
}
int ExprNode::getParaNum(){
    return funcParent->getParaNum();
}
// 将succ添加入后继表达式集合succExprs
void ExprNode::addSuccExpr(ExprNode* succ){
    succExprSet.insert(succ);
}

// 根据 AliveVarSet = (JOIN(V) - left) + right 计算活跃变量集
void ExprNode::calcAliveVarSet(){
    set<IdNode*> join, left, right;
    if(isLastInBlock())
        join = blockParent->getLastAliveVarSet();
    else
        join = calcJoinAliveVarSet();
    left = calcLeftValueVarSet();
    right = calcRightValueVarSet();
    aliveVarSet = set<IdNode*>();
    for(auto& id:join)
        aliveVarSet.insert(id);
    for(auto& id:left)
        aliveVarSet.erase(id);
    for(auto& id:right)
        aliveVarSet.insert(id);
}

// 只能在后继表达式计算完毕后使用
bool ExprNode::isLastInBlock(){
    return succExprSet.size()==0;
}

// 计算JOIN(v) = Union[succExprs.aliveVars]
set<IdNode*> ExprNode::calcJoinAliveVarSet(){
    set<IdNode*> joinSet;
    for(auto& succExpr:succExprSet){
        for(auto& aliveVar:succExpr->getAliveVarSet()){
            joinSet.insert(aliveVar);
        }
    }
    return joinSet;
}

set<IdNode*> ExprNode::getAliveVarSet(){
    return aliveVarSet;
}

// 计算作为右值的id集合
set<IdNode*> ExprNode::calcRightValueVarSet(){
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
        vector<IdNode*> paras = getParas();
        rightValueSet = set<IdNode*>(paras.begin(),paras.end());
    }
    else ; // do no thing
    return rightValueSet;
}

// 计算作为左值的id集合
set<IdNode*> ExprNode::calcLeftValueVarSet(){
    set<IdNode*> leftValueSet = set<IdNode*>();
    if(exprType==Op2Type||exprType==Op1Type||exprType==NoOpType
     ||exprType==VisitArrayType||exprType==CallType
     ||exprType==LocalDeclareType)
        leftValueSet.insert(getVar());
    return leftValueSet;
}
set<IdNode*> ExprNode::getLeftValueVarSet(){
    return calcLeftValueVarSet();
}
IdNode* ExprNode::getVar(){
    assert(exprType==Op2Type||exprType==Op1Type||exprType==NoOpType
     ||exprType==StoreArrayType||exprType==VisitArrayType
     ||exprType==CallType||exprType==LocalDeclareType);
    return (IdNode*)children[0]; // 需要检查
}
IdNode* ExprNode::getRightValue(){
    assert(exprType==Op1Type||exprType==NoOpType||exprType==ReturnType);
    if(exprType==Op1Type||exprType==NoOpType)
        return (IdNode*)children[1];
    else //(exprType==ReturnType)
        return (IdNode*)children[0];
}
IdNode* ExprNode::getRightValue1(){
    assert(exprType==Op2Type||exprType==StoreArrayType
     ||exprType==VisitArrayType||exprType==IfBranchType);
    if(exprType==Op2Type||exprType==StoreArrayType||exprType==VisitArrayType)
        return (IdNode*)children[1];
    else //(exprType==IfBranchType)
        return (IdNode*)children[0];
}   
IdNode* ExprNode::getRightValue2(){
    assert(exprType==Op2Type||exprType==StoreArrayType
    ||exprType==VisitArrayType||exprType==IfBranchType);
    if(exprType==Op2Type||exprType==StoreArrayType||exprType==VisitArrayType)
        return (IdNode*)children[2];
    else //(exprType==IfBranchType)
        return (IdNode*)children[1];
}
// 得到CallFunc的所有参数节点
vector<IdNode*> ExprNode::getParas(){
    assert(exprType==CallType);
    int l = children.size();
    // 排除左值children[0]
    vector<IdNode*> paras = vector<IdNode*>();
    stack<Node*> dfsStack = stack<Node*>();
    for(int i = l-1;i>=1;i--)
        dfsStack.push(children[i]);
    while(!dfsStack.empty()){
        Node* top = dfsStack.top();
        dfsStack.pop();
        if(top->getNodeType()==OtherNodeType){
            vector<Node*> otherchildren = top->getChildren();
            int len = otherchildren.size();
            for(int i = len-1;i>=0;i--)
                dfsStack.push(otherchildren[i]);
        }
        else if(top->getNodeType()==IdNodeType){
            paras.push_back((IdNode*)top);
        }
    }
    return paras;
}
bool ExprNode::isAlive(IdNode* id){
    return aliveVarSet.find(id)!=aliveVarSet.end();
}
bool ExprNode::isAliveNext(IdNode* id){
    if(next==NULL) return false;
    return next->isAlive(id);
}
void ExprNode::genCode(){
    cerr << "ExprNode::genCode starts" << endl;
    assert(funcParent!=NULL);
    code += (funcParent->getManager()).genCode(this);
    cerr << "ExprNode::genCode ends with code:" << code;
}
void ExprNode::printCode(){
    out << code;
}


/* ------------------ IdNode ------------------ */
// 一般变量的构造函数
IdNode::IdNode(string name_, bool ifGlobal_):Node(IdNodeType){
    name = name_;
    ifGlobal = ifGlobal_;
    ifArray = false;
    ifInteger = false;
    ifPara = (name[0]=='p');
    ifTemp = (name[0]=='t');
    ifCalleeSave = false;
    value = length = 0;
    funcParent = NULL;
}
// 数组的构造函数
IdNode::IdNode(string name_, bool ifGlobal_, int length_):Node(IdNodeType){
    name = name_;
    ifGlobal = ifGlobal_;
    ifArray = true;
    ifInteger = false;
    ifPara = false;
    ifTemp = (name[0]=='t');
    ifCalleeSave = false;
    length = length_;
    value = 0;
    funcParent = NULL;
}
// 整数的构造函数
IdNode::IdNode(int value_):Node(IdNodeType){
    name = string();
    ifArray = ifGlobal = false;
    ifInteger = true;
    ifPara = false;
    ifTemp = false;
    ifCalleeSave = false;
    value = value_;
    length = 0;
    funcParent = NULL;
}
//　CalleeSave寄存器对应的idNode的构造函数
IdNode::IdNode(int locate, bool ifCalleeSave):Node(IdNodeType){
    name = string();
    ifArray = ifGlobal = false;
    ifInteger = false;
    ifPara = false;
    ifTemp = false;
    ifCalleeSave = true;
    value = locate;
    length = 0;
    funcParent = NULL;
}
// 得到目标代码的Tigger名，全局变量将T改为v
string IdNode::getTiggerName(){
    string tiggerName;
    if(ifGlobal){
        tiggerName = name;
        tiggerName[0] = 'v';
    }
    else{
        tiggerName = name;
    }
    return tiggerName;
}
int IdNode::getLength(){
    assert(ifArray);
    return length;
}
int IdNode::getValue(){
    assert(ifInteger);
    return value;
}
bool IdNode::isArray(){
    return ifArray;
}
bool IdNode::isGlobal(){
    return ifGlobal;
}
bool IdNode::isInteger(){
    return ifInteger;
}
bool IdNode::isPara(){
    return ifPara;
}
bool IdNode::isLocal(){
    return !ifGlobal&&!ifInteger;
}
bool IdNode::isCalleeSave(){
    return ifCalleeSave;
}
// 退出一个block时，全局非数组变量/函数参数/非临时非数组变量需要保存
bool IdNode::needSave(){
    return (ifGlobal&&!ifArray)||ifPara||(!ifTemp&&!ifInteger&&!ifArray);
}
void IdNode::setFuncParent(FuncNode* funcParent){
    funcParent = funcParent;
}
// 名字相同则相等，若为整数则值相同就相等
bool operator==(const IdNode& here,const IdNode& another){
    if(here.ifInteger&&another.ifInteger)
        return here.value==another.value;
    else
        return here.name==another.name;
    return false;
}
