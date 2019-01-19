#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <cstring>
#include <map>
#include <cassert>
#include <algorithm>
#include "reg.h"    

using namespace std;

enum nodeType {FuncNode, ExprNode, IDNode, OpNode, IntNode, ExprListNode, GlobalListNode, DeclareNode, RootNode, GlobalDeclareNode};

class idType
{
    public:
        string name;
        int regsiter;
        int start, end;
        int spillTime;      // 执行完位于spillTime的表达式后入栈
        bool isGlobal;      // 是否是全局变量
        bool isArray;       // 是否是数组头
        // string globalName;  // 全局名字，如果有的话
        // int sz;             // 大小， 如果是数组的话
        bool removed;       // 是否被移出
        idType(string name_, int locate , bool isGlobal_ = false, bool isArray_ = false);
        idType();
        friend bool operator< (const idType& , const idType&);
        friend bool cmp(const idType&, const idType&);
        
};
class node
{
    public:
        nodeType type;
        node* parent;


        int paraNum;
        int stackUsed;
        int t;
        reg r;
        int paraCnt;    // 调用函数时用来计数

        int exprType; // range:[0-9]

        // for ExprNode, FuncNode and DeclareNode
        int lineNo;

        // for DeclareNode and GlobalDeclareNode
        int length;

        vector<node*> child;

        // for FuncNode
        vector<idType> idTable;
        vector<idType*> liveQueue;
        map<string, int> stackSpace;

        // for ID， DeclareNode, GlobalDeclareNode, FuncNode, OpNode, IntNode
        string name;
        // for ID
        bool isArray;
        // for ExprNode,
        string code;

        node(nodeType);
        node(int);  // expr quick path
        void add_child(node* );
        void adjust_child();
        void set_table();
        //void set_table(bool);
        //void mytraverse(node* );
        void allo_reg();
        void all_allo_reg();
        void gen_code();
        void all_gen_code();
        void print_code();
        idType search_table(string);
        int check_stack_space(string);
        void refresh_reg(node*);
        bool alive(const idType& i);
        bool in_reg(const idType& i);
        string load_in_reg(const idType& i, int k, bool);
        string store_id(const idType& i, int k);
        string store_int(int i, int k);
        string gen_right_value_code(const node* p, node* expr, int reg, bool keepInt, bool ifAddr);
        void print_tree();
        void allo_stack_space(string, int);
        void insert_liveQueue(idType*);
        void remove_liveQueue(int t);
        void show_self();
        
};
extern int exprCnt;
extern node* ancestor;

#endif