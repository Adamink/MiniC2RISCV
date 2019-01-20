#include "node.h"
#include "table.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;
int exprCnt = 0;
const int INF = 10007;
string globalUsed = string();
node* ancestor = NULL;
map<int, string> nodeTypeMap{
{0,"FuncNode"},
{1,"ExprNode"},
{2,"IDNode"},
{3,"OpNode"},
{4, "IntNode"},
{5, "ExprListNode"},
{6,"GlobalListNode"},
{7,"DeclareNode"},
{8,"RootNode"},
{9,"GlobalDeclareNode"}
};
// stringstream output;
idType::idType(string name_, int locate, bool isGlobal_, bool isArray_){
    name = name_;
    start = locate;
    end = locate;
    spillTime = INF;
    isGlobal = isGlobal_;
    isArray = isArray_;
    regsiter = -1;
    removed = false;
}
idType::idType(){
    name = "";
    start = 1;
    end = INF;
    spillTime = INF;
    isGlobal = false;
    isArray = false;
    regsiter = -1;
    removed = false;
}
bool operator< (const idType& id1, const idType& id2){
    return id1.end < id2.end;
}
bool cmp(const idType& id1, const idType& id2){
    return id1.start < id2.start;
}
node::node(nodeType type_):r(regNum){
    type = type_;
    child = vector<node*>();
    parent = NULL;

    idTable = vector<idType>();
    liveQueue = vector<idType*>();
    stackUsed = 0;
    paraNum = 0;
    stackSpace = map<string, int>();
    r = reg(regNum);
    paraCnt = 0;

    code = string();
    exprType = -1;
    lineNo = 1;
    length = 0;
    name = string();
    isArray = false;
}
node::node(int exprType_):r(regNum){
    // new (this) node(ExprNode);
    type = ExprNode;
    child = vector<node*>();
    parent = NULL;

    idTable = vector<idType>();
    liveQueue = vector<idType*>();
    stackUsed = 0;
    paraNum = 0;
    stackSpace = map<string, int>();
    r = reg(regNum);
    paraCnt = 0;

    code = string();
    exprType = -1;
    lineNo = 1;
    length = 0;
    name = string();
    exprType = exprType_;
    isArray = false;

}
void node::add_child(node* p){
    child.push_back(p);
    p->parent = this;
}
// extern int exprCnt;
// extern node* ancestor;
// 遇到某个变量时，根据行数更新它的周期
void setNameRange(node* p){
    string idName = p->name;
    int i = 0;
    int l = ancestor->idTable.size();
    bool isArray_ = p->isArray;

    for(i = 0; i < l; i++){
        if(ancestor->idTable[i].name == idName){
            ancestor->idTable[i].start = min(ancestor->idTable[i].start, exprCnt);
            ancestor->idTable[i].end = max(ancestor->idTable[i].end, exprCnt);
            // ancestor->idTable[i].spillTime = ancestor->idTable[i].end;
            return;
        }
    }
    if(i==l){//没找到，可能是第一次，也可能是全局变量
        if(globalTable.find(idName)!=globalTable.end()){
            //全局变量
            idType in = globalTable[idName];
            idType pushed_in = in;
            pushed_in.start = pushed_in.end = exprCnt;
            pushed_in.spillTime = INF;
            pushed_in.name = idName;
            ancestor->idTable.push_back(pushed_in);
        }
        else{
            //第一次遇到的局部变量
            ancestor->idTable.push_back(idType(idName, exprCnt,false, isArray_));
        }
    }
}
// 被递归调用用来得到每个变量的周期
void traverse(node* p){
    if(p->type==ExprNode){
        exprCnt = p->lineNo;
    }
    else if(p->type==DeclareNode){
        exprCnt = p->lineNo;
        setNameRange(p);
    }
    else if(p->type==IDNode){
        setNameRange(p);
    }
    for(auto &it:p->child){
        traverse(it);
    }
}
// 被递归调用来调整并去掉无用的节点并计算行数
// 对于RootNode，它的孩子是所有的函数定义和全局变量声明，每个函数从1开始对应一个lineNo
// 对于FuncNode, 它的孩子是所有的表达式，每个表达式从1开始对应一个lineNo
void get_child(nodeType rootType, vector<node*> & v, node* p){
    if(rootType==FuncNode){
        for(auto& it:p->child){
            if(it->type==ExprNode||it->type == DeclareNode){
                v.push_back(it);
                it->parent = ancestor;
                it->lineNo = v.size();
            }
            else get_child(rootType, v, it);
        }
    }
    else if(rootType==RootNode){
        for(auto& it:p->child){
            if(it->type==FuncNode||it->type==GlobalDeclareNode){
                v.push_back(it);
                it->parent = ancestor;
                it->lineNo = v.size();
            }
            else get_child(rootType, v, it);
        }
    }
}
// 调整并去掉无用的节点并计算行数   
void node::adjust_child(){
    assert (type==RootNode);
    vector<node* > ret = vector<node*>();
    ancestor = this;
    get_child(type, ret, this);
    while(!child.empty()) child.pop_back();
    for(auto& it:ret)
        child.push_back(it);
    for(auto& it:child){
        vector<node*> ret1 = vector<node*>();
        ancestor = it;
        get_child(FuncNode, ret1, it);
            while(!it->child.empty()) it->child.pop_back();
        for(auto& jt:ret1)
            it->child.push_back(jt);
        // it->child = ret1;
    }
}
// 为RootNode的所有FuncNode的所有变量计算时间周期
// 同时得到globalTable，顺便生成globalDeclareNode的code
void node::set_table(){
    assert (type==RootNode);
    for(auto& it:child){
        if(it->type==FuncNode){ // 函数
            exprCnt = 1;
            ancestor = it;
            for(int i = 0;i<it->paraNum;i++){
                string paraName = string("p") + string(to_string(i));
                node* p = new node(IDNode);
                p->name = paraName;
                p->isArray = false;
                setNameRange(p);
            }
        traverse(it);
        }
        else{ // 全局变量
            idType id = check_table(it->name, it->isArray);
            string s = id.name;
            
            if(it->length==0){ // 整数变量
                it->code = s + " = 0\n"; 
            }
            else{ //数组变量
                it->code = s + " = malloc " + to_string(it->length) + "\n";
            }
        }
    }
}
/*
void node::set_table(bool is){
    assert (type==RootNode);
    for(auto& it:child){
        if(it->type==FuncNode){
            ancestor = this;
            exprCnt = 1;
            for(int i = 0;i<paraNum;i++){
                string paraName = string("p") + string(to_string(i));
                // cout << paraName << endl;
                // idType* p = new idType(paraName, exprCnt, false, false);
                // setNameRange(it);
                //node* p = new node(IDNode);
                //p->name = paraName;
                //p->isArray = false;
                idType p = idType();
                p.name = paraName;
                idTable.push_back(p);
                //setNameRange(p);
            }
            mytraverse(this);
            //mytraverse(this);
        }
        else{ // 全局变量
            idType id = check_table(it->name, it->isArray);
            string s = id.name;
            
            if(it->length==0){ // 整数变量
                it->code = s + " = 0\n"; 
            }
            else{ //数组变量
                it->code = s + " = malloc " + to_string(it->length);
            }
        }
    }
}*/
/*
void node::mytraverse(node* p){
    if(p->type==ExprNode||p->type==DeclareNode){
        //exprCnt++;
        // exprCnt = p->lineNo;
    }
    else if(p->type==IDNode){
        // setNameRange(p);
        int l = idTable.size();
        bool found = false;
        for(int i =0;i<l;i++){
            if(idTable[i].name == p->name){
                found = true;
                break;
            }
        }
        if(!found){
            if(globalTable.find(p->name)!=globalTable.end()){
                idType in = globalTable[p->name];
                idType pushed_in = in;
                pushed_in.name = p->name;
                idTable.push_back(pushed_in);
            }
            else{
                idType in = idType();
                in.name = p->name;
                in.isArray = p->isArray;
                idTable.push_back(in);
            }
        }
    }
    for(auto &it:p->child){
        mytraverse(it);
    }
}*/
// 根据it的结束时间将it有序插入队列
void node::insert_liveQueue(idType* it){
    vector<idType*>::iterator jt;
    for(jt = liveQueue.begin();jt!=liveQueue.end();++jt){
        if((**jt).end >= it->end) break;
    }
    liveQueue.insert(jt, it);
}
// 将周期已经结束的变量移出队列
void node::remove_liveQueue(int t){

    bool inLoop = false;
    while(true){
        int l = liveQueue.size();
        for(int i=0;i<l;i++){
            if((liveQueue[i])->end < t){
                for(int j = i;j<l-1;j++)
                    liveQueue[j] = liveQueue[j+1];
                inLoop = true;
                liveQueue.pop_back();
            }
            if(inLoop) break;
        }
        if(!inLoop) break;
    };
}
// 给每个idTable中的变量分配寄存器及失效时间
void node::allo_reg(){
    assert(type==FuncNode);

    // 按执行顺序排序idTable
    sort(idTable.begin(), idTable.end(),cmp);
    //char* newChar = new char[2000];
    //newChar[0] = '\0';
    //cout <<newChar <<endl;
    r = reg(paraNum);
    int previous = 0;
    for(auto& it:idTable){
        if(it.name.substr(0,1)=="p"){
            int dst = stoi(it.name.substr(1,1));
            it.regsiter = dst;
            r.regList[dst] = 1;
        }
    }
    for(auto& it:idTable){
        if(it.regsiter!=-1) continue; // p staff
        if(!r.full())
            it.regsiter = r.acquire();
        else{
            it.regsiter = -1;
        }
    }

    int linearScan = previous;
    if(linearScan){
    for(auto& it:idTable){

        // 释放周期已经结束的变量对应的寄存器
        for(auto& jt:liveQueue){
            if(jt->end < it.start){
                r.release(jt->regsiter);
            }
        }
        // 并从队列中移除
        remove_liveQueue(it.start);
        
        // 给从start开始的变量it分配寄存器

        // 寄存器未满直接分配寄存器
        if(!r.full()){
            it.regsiter = r.acquire();
            insert_liveQueue(&it);
        }
        // 寄存器已满
        else{
            idType* last = liveQueue.back();
            // 队尾变量截止时间晚，将队尾变量入栈，
            // 给it分配寄存器并入队
            if(last->end > it.end){
                last->spillTime = it.start - 1;
                r.release(last->regsiter);
                liveQueue.pop_back();
                it.regsiter = r.acquire();
                insert_liveQueue(&it);
            }
            // 队尾变量截止时间早，将it入栈
            else {
                it.regsiter = -1;
            }
        }
    }
    }
}
// 供根节点调用，给每个函数里的id分配寄存器
void node::all_allo_reg(){
    assert(type==RootNode);
    for(auto& it:child){
        if(it->type==FuncNode)
            it->allo_reg();
    }
}

// 在栈空间中查找名字，如果有则返回位置，没有则新建条目返回位置，且增加stackUsed
int node::check_stack_space(string s){
    assert(type==FuncNode);
    //cerr << "check_stack_space called" << endl;
    if(stackSpace.find(s)!=stackSpace.end()){
        //cerr << "\t" << s << " " << stackSpace[s] << endl;
        return stackSpace[s];
    }
    else{
        // changeed 
        //cerr << "before insert" << endl;
        stackSpace[s] = stackUsed;
        //cerr << "after insert" << endl;
        // cerr << "\t" << s << " " << stackSpace[s] << endl;
        // cerr << "could return" <<endl;
        return stackUsed++;
    }
}
// 向栈空间中插入名字s，并分配空间增加stackUsed
void node::allo_stack_space(string s,int l){
    assert(type==FuncNode);
    stackSpace[s] = stackUsed;
    stackUsed += l;
}
// id是否此刻活跃
bool node::alive(const idType& i){
    return (i.start<=t&&i.spillTime>=t)&&i.regsiter != -1;
}
// id是否此刻在寄存器中
bool node::in_reg(const idType& i){
    return alive(i)&&r.regList[i.regsiter]==1;
}
// 将i移入寄存器k，返回代码字符串
string node::load_in_reg(const idType& i, int k = -1, bool ifAddr = false){
    //cerr << i.name << " " <<i.start << " "<<i.spillTime <<" "<< i.isGlobal<<" " << i.isArray<<" "<<endl;
    //cerr << i.name << " " << i.regsiter << endl;
    string ret = string();
    string dst;
    if(k==-1){
        k = i.regsiter;
    }
    r.regList[k] = 1;   
    dst = regMap[k];

    // 注意，在callee_save返回true后callee_save被置为false,只保存一次
    if(r.callee_save(k)){
        int locate = check_stack_space(to_string(k));
        ret += "store " + regMap[k] + " " + to_string(locate) + "\n";
        // cerr << ret << endl;
    }
    // cerr << ret;
    // cerr << "finish save" << endl;
    string load;
    if(ifAddr||i.isArray) load = "loadaddr ";
    else load = "load ";
    //if(i.isArray&&i.isGlobal) load = "loadaddr ";
    // cerr << load << endl;
    string tmp = string();
    if(i.isGlobal){
        tmp = load + globalTable[i.name].name + " " + dst + "\n";
        //cerr << tmp;
        //cerr << ret;
        ///int l =tmp.length() + ret.length();
        // string s = string(tmp2);
        ret += tmp;
        // cerr << ret;
    }
    else{
        ret += load + to_string(check_stack_space(i.name)) + " " + dst + "\n";
    }
    //cerr << "here"<<endl;
    //cerr <<"return load in reg"<<endl;
    // cerr << "liupeiju" << endl;
    return ret;
}
// 将寄存器k中的id存入自己原来的位置，返回代码字符串
string node::store_id(const idType& i,int k = -1){
    string src;
    assert(!(i.regsiter==-1&&k==-1));
    if(k==-1){
        k = i.regsiter;
        src = regMap[i.regsiter];
        r.regList[i.regsiter] = 0;
    }
    else{
        src = regMap[k];
        r.regList[k] = 0;
    }
    
    string ret = string();
    if(i.isGlobal){
        ret+= "loadaddr " + globalTable[i.name].name + " " + regMap[regMem] +  "\n";
        ret+= regMap[regMem] + "[0] = " + src + "\n";
    }
    else{
        ret+= "store " + src + " " + to_string(check_stack_space(i.name)) + "\n";
    }

    return ret;
}
// 即将执行Expr
void node::refresh_reg(node* expr){
    assert(type==FuncNode);
    int t = expr->lineNo;
    for(auto& it:idTable){
        /*
        cerr << it.name << " " << it.start << " " << it.spillTime <<" " << in_reg(it)<< " " <<alive(it) <<" " << it.isArray << endl; */
        if(it.spillTime==t-1){//移出
            // cerr << "try store "<< it.name << endl;
            expr->code+= store_id(it);
        }
        if(it.start==t){//移入寄存器
            // 如果是函数调用之后呢？还需要移入么
            if(it.name[0]=='p') continue; // 参数不需要移入
            // 数组需要移入, 全局变量需要移入
            if(it.isArray||it.isGlobal)
            {
                //cerr << "before load" << endl;
                string tmpp = load_in_reg(it);
                //cerr << "tmp:"<<tmpp;
                //cerr << "exprcode: " << expr->code << "finished "<<endl;
                // expr->show_self();
                // int len = tmpp.length();
                //cerr << len << endl;
                //expr->code = string(len, 'a');
                // cerr << "assign scc" << endl;
                expr->code+=tmpp;
                //cerr << "load_in_reg succ" << endl;
            }
        }
        // 在函数调用时被移出了需要再移入
        /*else if(it.start <= t &&it.spillTime >= t && !in_reg(it)){
            expr->code+= load_in_reg(it);
        }*/
        if(it.removed&&it.start<t &&it.spillTime>=t&&!in_reg(it)){
            expr->code += load_in_reg(it);
            it.removed = false;
        }
    }
}
// return a namxe of register
string node::gen_right_value_code(const node* p, node* expr, int reg, bool keepInt = false, bool ifAddr = false){
    assert(type==FuncNode);
    if(p->type==IntNode){
        if(keepInt) return p->name;
        else{
            if(p->name=="0") return regMap[zero];
            else{
                expr->code+= regMap[reg] + " = " + p->name + "\n";
                return regMap[reg];
            }
        }
    }
    else{
        idType id = search_table(p->name);
        string ret;
        if(!alive(id)){
            ret = regMap[reg];
            expr->code+= load_in_reg(id, reg, ifAddr);
        }
        else ret = regMap[id.regsiter];
        return ret;
    }
}
// FuncNode生成对应的code
void node::gen_code(){
    assert(type==FuncNode);
    r = reg(paraNum);
    
    stringstream output;
    for(auto& expr:child){
        t = expr->lineNo;
        // assert(expr->type>=0);
        // 将该移出寄存器的变量都移出，将该进入寄存器的变量都进入
        // 除非正在准备调用函数
        expr->code = string();
        if(expr->type==DeclareNode){
            if(expr->length==0){
                //allo_stack_space(expr->name, )
                // 不一定需要分配栈空间，不操作
            }
            else{
                // 数组，分配栈空间
                allo_stack_space(expr->name, expr->length / 4);
            }
        }
        if(paraCnt==0) refresh_reg(expr);

        if(expr->type==ExprNode){
        // ID ASSIGN RightValue Op2 RightValue
        if(expr->exprType==0){
            
            node* idNode = expr->child[0];
            node* rightValue1 = expr->child[1];
            node* op = expr->child[2];
            node* rightValue2 = expr->child[3];

            idType id0 = search_table(idNode->name);
            string id0_reg;// = regMap[id0.regsiter];
            if(!alive(id0)){
                id0_reg = regMap[reg0];
            }
            else{
                id0_reg = regMap[id0.regsiter];
            }
            
            
            bool calFirst = false;
            string id1_reg, id2_reg;
            if(rightValue1->type==IntNode&&rightValue2->type==IntNode){
                int calResult = 0;
                int first = stoi(rightValue1->name);
                int second = stoi(rightValue2->name);
                // PLUS | MINUS | TIME | DIVIDE | MOD | AND | OR | LESS | GREATER | EQUAL | NOTEQUAL
                string tmp = op->name;
                if(tmp=="+")
                    calResult = first + second;
                else if(tmp=="-")
                    calResult = first - second;
                else if(tmp=="*")
                    calResult = first * second;
                else if(tmp=="/")
                    calResult = first / second;
                else if(tmp=="%")
                    calResult =first % second;
                else if(tmp=="&&")
                    calResult = first && second;
                else if(tmp=="||") 
                    calResult = first || second;
                else if(tmp=="<")
                    calResult = (first < second);
                else if(tmp==">")
                    calResult = (first > second);
                else if(tmp=="==")
                    calResult = (first == second);
                else if(tmp=="!=")
                    calResult = (first !=second);
                else
                    assert(false);
                expr->code = id0_reg + " = " + to_string(calResult) + "\n";
                calFirst = true;
            }
            else if (rightValue1->type==IntNode){
                if(rightValue1->name=="0") 
                    id1_reg = regMap[zero];
                else {
                    id1_reg = regMap[reg1];
                    expr->code+= id1_reg + " = " + rightValue1->name + "\n";
                }
                idType id2 = search_table(rightValue2->name);
                //id2_reg = regMap[id2.regsiter];
                if(!alive(id2)){
                    id2_reg = regMap[reg2];
                    expr->code+=load_in_reg(id2, reg2);
                }
                else{
                    id2_reg = regMap[id2.regsiter];
                }
            }
            else{
                idType id1 = search_table(rightValue1->name);
                id1_reg;// = regMap[id1.regsiter];
                if(!alive(id1)){
                    id1_reg = regMap[reg1];
                    expr->code+=load_in_reg(id1, reg1);
                }
                else{
                    id1_reg = regMap[id1.regsiter];
                }
                if(rightValue2->type==IntNode){
                    if(op->name=="+"||op->name=="<"){
                        id2_reg = rightValue2->name;
                    }
                    else{
                        id2_reg = regMap[reg2];
                        expr->code+= id2_reg + " = " + rightValue2->name + "\n";
                    }
                }
                else{
                    idType id2 = search_table(rightValue2->name);
                    id2_reg;// = regMap[id2.regsiter];
                    if(!alive(id2)){
                        id2_reg = regMap[reg2];
                        expr->code+=load_in_reg(id2, reg2);
                    }
                    else{
                        id2_reg = regMap[id2.regsiter];
                    }
                }
            }
            if(!calFirst){
                expr->code+=id0_reg + " = " + id1_reg + " " + op->name + " " + id2_reg + "\n";
            }
            if(!alive(id0)){
                expr->code+=store_id(id0, reg0);
            }
            else{
                r.regList[id0.regsiter] = 1;
            }
        }
        // ID ASSIGN Op1 RightValue
        else if(expr->exprType==1){
            
            node* idNode = expr->child[0];
            node* op = expr->child[1];
            node* rightValue1 = expr->child[2];
            
            idType id0 = search_table(idNode->name);
            string id0_reg;//= regMap[id0.regsiter];
            if(!alive(id0)){
                id0_reg = regMap[reg0];
            }
            else{
                id0_reg = regMap[id0.regsiter];
            }
            // warning!
            if(rightValue1->type==IntNode){
                expr->code+= id0_reg + " = " + op->name + rightValue1->name + "\n";
            }
            else{
                idType id1 = search_table(rightValue1->name);
                string id1_reg = regMap[id1.regsiter];
                if(!alive(id1)){
                    // expr->code+= load_in_reg(id1, reg1);
                    id1_reg = regMap[reg1];
                }
                expr->code+= id0_reg + " = " + op->name + " " + id1_reg + "\n";
            }
            if(!alive(id0)){
                expr->code+=store_id(id0,reg0);
            }
            else{
                r.regList[id0.regsiter] = 1;
            }
        }
        // ID LBRAC RightValue RBRAC ASSIGN RightValue
        else if(expr->exprType==2){
            
            node* idNode = expr->child[0];
            node* rightValue1 = expr->child[1];
            node* rightValue2 = expr->child[2];

            idType id0 = search_table(idNode->name);
            //string id0_reg = regMap[id0.regsiter];
            string id0_reg = gen_right_value_code(idNode, expr, reg0,false, true);
            string id1_reg = gen_right_value_code(rightValue1, expr, reg1, true, false);
            string id2_reg = gen_right_value_code(rightValue2, expr, reg2, false, false);
            expr->code += regMap[reg0]  + " = " + id0_reg + " + " + id1_reg  + "\n";
            expr->code += regMap[reg0] + "[0] = " + id2_reg + "\n";

                        /*
            if(!alive(id0)){
                id0_reg = regMap[reg0];
                expr->code+= load_in_reg(id0, reg0, true);
            }
            else id0_reg = regMap[id0.regsiter];

            string id2_reg;
            if(rightValue2->type==IntNode){
                id2_reg = regMap[reg2];
                expr->code+= id2_reg + " = " + rightValue2->name + "\n";
            }
            else{
                idType id2 = search_table(rightValue2->name);
                id2_reg = regMap[id2.regsiter];
                cerr << "id2_Reg: " << id2_reg << endl;
                if(!alive(id2)){
                    id2_reg = regMap[reg2];
                    expr->code+= load_in_reg(id2, reg2);
                }
                // cerr << "id2_Reg: " << id2_reg << endl;
            }
            if(rightValue1->type==IntNode){
                expr->code+= id0_reg + "[" + rightValue1->name +"] = "+ id2_reg + "\n";
            }
            else{
                idType id1 = search_table(rightValue1->name);
                string id1_reg = regMap[id1.regsiter];
                if(!alive(id1)){
                    id1_reg = regMap[reg1];
                    expr->code+= load_in_reg(id1, reg1);
                }
                // cerr << "id2_reg:" << id2_reg << endl;
                expr->code+= regMap[reg0] + " = "  + id0_reg + " + " + id1_reg + "\n";
                expr->code+= regMap[reg0] + "[0] = " + id2_reg + "\n"; 
                // cerr << "branch " << expr->code;
            }*/
        }
        // ID ASSIGN ID LBRAC RightValue RBRAC
        else if(expr->exprType==3){
            node* id0 = expr->child[0];
            node* id1 = expr->child[1];
            node* rightValue2 = expr->child[2];
            idType id0_ = search_table(id0->name);

            if(rightValue2->type==IDNode){
                string id0_reg = gen_right_value_code(id0, expr, reg0);
                string id1_reg = gen_right_value_code(id1, expr, reg1, false, true);
                string id2_reg = gen_right_value_code(rightValue2, expr, reg2, false, false);
                expr->code+= regMap[reg1] + " = " + id1_reg + " + " + id2_reg + "\n";
                expr->code+= id0_reg + " = " + regMap[reg1] + "[0]\n";
            }
            else{
                string id0_reg = gen_right_value_code(id0, expr, reg0);
                string id1_reg = gen_right_value_code(id1, expr, reg1);
                expr->code+= id0_reg + " = " + id1_reg + "[" + rightValue2->name + "]\n";
            }
            if(!alive(id0_)){
                expr->code+=store_id(id0_, reg0);
            }
            else{
                r.regList[id0_.regsiter] = 1;
            }
        }
        // IF RightValue LogicalOp RightValue GOTO LABEL
        else if(expr->exprType==4){
            
            node* id1 = expr->child[0];
            node* op = expr->child[1];
            node* id2 = expr->child[2];

            string id1_reg = gen_right_value_code(id1, expr, reg1, false);
            string id2_reg = gen_right_value_code(id2, expr, reg2, false);
            expr->code+= "if " + id1_reg + " " + op->name + " " + id2_reg + " goto " + expr->name + "\n";
        }
        // GOTO LABEL
        else if(expr->exprType==5){
            expr->code+= "goto " + expr->name + "\n";
        }
        // LABEL COLON
        else if(expr->exprType==6){
            expr->code+=expr->name + ":\n";
        }
        // PARAM RightValue
        else if(expr->exprType==7){
            node* rightValue1 = expr->child[0];
            for(auto& it:idTable){
                if(it.regsiter == paraCnt&&in_reg(it)){
                    expr->code+= store_id(it);
                }
            }

            string name = gen_right_value_code(rightValue1, expr, paraCnt, true, false);
            expr->code += regMap[paraCnt] + " = " + name + "\n";
            
            //gen_right_value_code(rightValue1, expr, paraCnt, false);
            paraCnt++;
        }
        // ID ASSIGN CALL FUNC
        else if(expr->exprType==8){
            // 保存caller_save寄存器中的活跃变量
            for(auto& it:idTable){
                if(r.caller_save(it.regsiter)&&in_reg(it)){
                    expr->code+= store_id(it);
                    it.removed = true;
                }
            }
            //cerr << "reach me!" <<endl;
            expr->code+= "call " + expr->name + "\n";
            
            node* id0 = expr->child[0];
            idType id0_ = search_table(id0->name);

            //expr->code+= id0_reg + " = " + regMap[0] + "\n";
            if(!alive(id0_)){ // !alive
                expr->code+=store_id(id0_,0);
            }
            else{// alive
                string id0_reg = gen_right_value_code(id0, expr, reg0); // 数组问题
                expr->code+= id0_reg + " = " + regMap[0] + "\n";
                r.regList[id0_.regsiter] = 1;
            }
            paraCnt = 0;
            // cerr<<"\t"<<expr->code<<endl;
            // 之后交给下一个表达式开始时候的重新移入
        }
        // RETURN RightValue
        else if(expr->exprType==9){
            // 保存全局变量
            for(auto& it:idTable){
                if(it.isGlobal&&!it.isArray&&in_reg(it)){
                    expr->code+= store_id(it);
                }
            }

            // 设置t0
            node* id0 = expr->child[0];
            if(id0->type==IntNode){
                expr->code+= regMap[0] + " = " + id0->name + "\n";
                // cout<<"reach here" <<endl;
            }
            else{
                idType id0_ = search_table(id0->name);
                if(!alive(id0_)){
                    expr->code+= load_in_reg(id0_, 0);
                }
                else{
                    expr->code+= regMap[0] + " = " + regMap[id0_.regsiter] + "\n";
                }
            }
            //cerr << "\t\t return rightvalue:" << "return value set finished"<<endl;
            // 恢复栈中callee_save的寄存器
            for(auto & p:stackSpace){
                int tmp;
                // cerr << p.first << " " << p.second << endl;
                if(isdigit(p.first[0])&&!(tmp=r.caller_save(stoi(p.first)))){
                    expr->code+="load " + to_string(p.second) + " " + regMap[stoi(p.first)] + "\n";
                } 
            }
            //cerr << "\t\t return rightvalue:" << "restore callee save reg finished" << endl;
            expr->code+="return\n";
            // cerr<<expr->code<<endl;
        }
        // CALL Func
        else if(expr->exprType==10){
            for(auto& it:idTable){
                if(r.caller_save(it.regsiter)&&in_reg(it)){
                    expr->code+= store_id(it);
                    it.removed = true;
                }
            }
            expr->code+= "call " + expr->name + "\n";
            paraCnt = 0;
        }
        // ID ASSIGN RightValue
        else if(expr->exprType==11){
            node* idNode = expr->child[0];
            node* rightValue1 = expr->child[1];

            idType id0 = search_table(idNode->name);
            string id0_reg;// = regMap[id0.regsiter];
            if(!alive(id0)){
                id0_reg = regMap[reg0];
            }
            else{
                id0_reg = regMap[id0.regsiter];
            }
            if(rightValue1->type==IntNode){
                expr->code+= id0_reg + " = " +  rightValue1->name + "\n";
            }
            else{
                idType id1 = search_table(rightValue1->name);
                string id1_reg;// = regMap[id1.regsiter];
                if(!alive(id1)){
                    // expr->code+= load_in_reg(id1, reg1);
                    //id1_reg = regMap[reg1];
                    // may problem
                    id1_reg = gen_right_value_code(rightValue1, expr, backMap[id0_reg], false, false);
                }
                else{
                    id1_reg = regMap[id1.regsiter];
                    expr->code+= id0_reg + " = " + id1_reg + "\n";

                }
            }
            if(!alive(id0)){
                expr->code+=store_id(id0,reg0);
            }
            else{
                r.regList[id0.regsiter] = 1;
            }
        }

        //cout<< expr->code;
    }
        output << expr->code;
    }

    
    cout <<name << " [" << paraNum << "] [" << stackUsed << "]" << endl;
    cout << output.str();
    cout << "end " << name <<endl;
}
// 遍历FuncNode都生成code
void node::all_gen_code(){
    assert(type ==RootNode);
    for(auto& it:child){
        if(it->type==FuncNode){
            it->gen_code();
        }
        else if (it->type==GlobalDeclareNode){ 
            cout << it->code;
        }
    }
}
// 从根节点打印输出
void node::print_code(){
    assert(type ==RootNode);

    for(auto& it:child){
        if(it->type==FuncNode){

            cout <<it->name << " [" << it->paraNum << "] [" << it->stackUsed << "]" << endl;


            for(auto& jt:it->child){

                assert(jt->type==ExprNode||jt->type==DeclareNode);
                cout << jt->code;
            }
            cout<<"end " << it->name<<endl;
        }
        else if(it->type==GlobalDeclareNode){
            cout<<it->code;
        }
    }
}
// 返回根据变量名返回table中的entry
idType node::search_table(string s){
    assert(type==FuncNode);
    for(auto& it:idTable){
        if(it.name==s) return it;
    }
    return idType("error", -1);
}
void node::print_tree(){
    show_self();
    for(auto& it:child){
        it->print_tree();
    }
};

void node::show_self(){
    /*
    cerr << "++++++++++++++++++++++" << endl;
    cerr << nodeTypeMap[type] << " size: " << sizeof(idType) << endl; 
    cerr << "name: " << name << " " << "size: " << name.length()<<endl;
    cerr << "regsize: " << sizeof(reg) << endl;
    cerr << "paraNum: " << paraNum << "stackUsed: " << stackUsed << "paraCnt: " << paraCnt << "exprType: " << exprType << "lineNo: " << lineNo << "length: " <<length << "isArray: " << isArray << endl;
    cerr << "codesize: " << code.length() << endl;
    cerr << "code: " << endl;
    cerr << code << endl;
    cerr <<"idTablesize: " << idTable.size() << endl;
    cerr << "liveQueuesize:"  <<liveQueue.size() << endl;
    cerr <<"stackSpacesize: " << stackSpace.size() << endl;
    cerr << "childsize: " <<child.size()<<endl;
    if(child.size()>0){
        for(auto& it:child)
            it->show_self();
    }*/
}