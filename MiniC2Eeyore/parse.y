%{
#include "util.h"
#include "node.h"
#include "type.h"
#include "env.h"
using namespace std;
#define YYERROR_VERBOSE 1
%}
/* generate include-file with symbols and types */
%defines
%locations

/* a more advanced semantic type */
%union {
    int ival;
    char* sval;
    Node* nval;
}
%token <ival> TYPE INTEGER PLUS MINUS TIME DIVIDE MOD NOT AND OR LESS GREATER EQUAL NOTEQUAL ASSIGN IF ELSE WHILE RETURN MAIN DOUBLEPLUS DOUBLEMINUS
%token <sval> '(' ')' '[' ']' '{' '}' ';' ',' ID
%type <nval> VarDefn FuncDefn FuncDecl Statement Statements Program ParaList ParaDecl Expression Block GlobalList ExprList BoolExpr

%nonassoc IF
%nonassoc ELSE
%right RETURN
%right ASSIGN
%left OR
%left AND
%left EQUAL NOTEQUAL
%left LESS GREATER
%left PLUS MINUS
%left TIME DIVIDE MOD
%right NOT UMINUS DOUBLEPLUS DOUBLEMINUS

%start Program
%%
Program:    
    GlobalList
    {
            Node* ret = new RootNode();
            ret->addChild($1);
            ret->finishParsing();
            $$ = ret;
    }
    ;
GlobalList:
    VarDefn GlobalList
    {
        Node* ret = new OtherNode();
        ret->addChild($1);
        ret->addCHild($2);
        $$ = ret;
    }
    |
    FuncDefn GlobalList
    {
        Node* ret = new OtherNode();
        ret->addChild($1);
        ret->addChild($2);
        $$ = ret;
    }
    |
    FuncDecl GlobalList
    {
        Node* ret = new OtherNode();
        ret->addChild($1);
        ret->addChild($2);
        $$ = ret;
    }
    |
    /* empty */
    {
        $$ = new EmptyNode();
    }
    ;
VarDefn:
    TYPE ID ';'
    {
        // this part could be added to createIdEntry
        createIdEntry($2, IntType, @2);
        string name = getIdName($2);
        string code = "var " + name + "\n";
        Node* ret = new StatementNode();
        ret->appendCode(code);
        $$ = ret;
    }
    |
    TYPE ID '[' INTEGER ']' ';'
    {
        createIdEntry($2, ArrayType, @2);
        string name = getIdName($2);
        string code = "var " + to_string(4*$4) + " " + name + "\n";
        Node* ret = new StatementNode();
        ret->appendCode(code);
        $$ = ret;
    }
    |
    error ';'
    {
        printDebugInfo("wrong definition method", @2);
        $$ = new OtherNode();
    }
    ;
ParaDecl:
    TYPE ID
    {
        Node* ret = new ParaNode($2,IntType);
        $$ = ret;
    }
    |
    TYPE ID '[' INTEGER ']'
    {
        Node* ret = new ParaNode($2,ArrayType);
        $$ = ret;
    }
    |
    TYPE ID '[' ']'
    {
        Node* ret = new ParaNode($2,ArrayType);
        $$ = ret;
    }
    TYPE
    {
        Node* ret = new ParaNode(IntType);
        $$ = ret;
    }
    |
    TYPE '[' ']'
    {
        Node* ret = new ParaNode(ArrayType);
        $$ = ret;
    }
    ;
ParaList:
    ParaDecl ',' ParaList
    {
        Node* ret = new ParaListNode();
        ret->addChild($1);
        ret->addChild($3);
    }
    |
    /* empty */
    {
        $$ = new ParaListNode();
    }
    ;
FuncDecl:
    TYPE ID '(' ParaList ')' ';'
    {
        Node* ret = new FuncNode();
        string name = string($2);
        createFuncEntry(name, DeclType, $4, @2);
        $$ = ret;
    }
    TYPE ID '(' ')' ';'
    {
        Node* ret = new FuncNode();
        string name = string($2);
        createFuncEntry(name, DeclType, NULL, @2);
        $$ = ret;
    }
    ;
FuncDefn:
    TYPE ID '(' ParaList ')' '{'
    {
    /*
    * check func's compatability with previous ones
    * if ok, if FuncDefn set paraList and insert them to idTable
    *        insert funcEntry to funcTable for future check
    */
        createFuncEntry(name, DefnType,$4, @2);
    }
    Block '}' 
    {
        Node* ret = new FuncNode();
        ret->addChild($8);
        int paraNum = getParaNum($4);
        string codeBefore = "f_" + $2 + " [" +to_string(paraNum) + "]\n";
        string codeAfter;

        // add return automatically
        int hasReturn = checkReturn(ret);
        if(!hasReturn)
            codeAfter = "return\n" + "end f_" + $2 + "
            \n";
        else
            codeAfter = "end f_" + $2 +"\n";
        ret->appendCodeBefore(codeBefore);
        ret->appendCodeAfter(codeAfter);
        $$ = ret;

        // exit func
        endScope();
        funcName = string();
    }
    ;
// a block that can be seen as one statement
Block:
    Statement
    {
        Node* ret = new OtherNode();
        ret->addChild($1);
        $$ = ret;
    }
    |
    '{' {newScope();} Statements '}'
    {
        endScope();
        $$ = $3;
    }
    |
    IF '(' BoolExpr ')' Block
    {
        Node* ret = new Node();
        ret->addChild($3);
        ret->addChild($5);
        string l = newLabel();
        string jmpCode = "if " + $3->valueID + " == 0 goto " + l + "\n";
        ret->appendCodeMiddle(jmpCode);
        ret->appendCodeAfter(l + ":\n");
        $$ = ret;
    } % prec IF
    |
    IF '(' BoolExpr ')' Block ELSE Block
    {
        Node* midNode = new Node();
        midNode.addChild($5);
        midNode.addChild($7);
        Node* ret = new Node();
        ret->addChild($3);
        ret->addChild(midNode);
        $$ = ret;
        string l1 = newLabel();
        string l2 = newLabel();
        string jmp1 = "if " + $3->valueID + " == 0 goto " + l1 + "\n";
        string jmp2 = "goto " + l2 + "\n";
        midNode->appendCodeBefore(jmp1);
        midNode->appendCodeMiddle(jmp2 + l1 + ":\n");
        midNode->appendCodeAfter(l2+":\n");
    } %prec ELSE
    |
    WHILE '(' BoolExpr ')' Block
    {
        Node* ret = new Node();
        ret->addChild($3);
        ret->addChild($5);
        string l1 = newLabel();
        string l2 = newLabel();
        string jmp1 = "if " + $3->valueID + " == 0 goto " + l2 + "\n";
        string jmp2 = "goto " + l1 + "\n";
        ret->appendCodeMiddle(l1 + ":\n" + jmp1);
        ret->appendCodeAfter(jmp2 + l2 + ":\n");
        $$ = ret;
    }
    ;
// continuous many statements
Statements:
    Block Statements
    {
        Node* ret = new OtherNode();
        ret->addChild($1);
        ret->addChild($2);
        $$ = ret;
    }
    |
    /* empty */
    {
        Node* ret = new EmptyNode();
        $$ = ret;
    }
    ;
// literally a single statement
Statement:



    Expression ';'
    {
        $$ = $1;
    }
    |
    VarDefn
    {
        $$ = $1;
    }
    |
    RETURN Expression ';'
    {

    }
    ;
%%
void yyerror(char *s) {
    printError(s);
}