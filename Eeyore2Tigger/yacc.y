%{
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <set>
#include "node.h"
using namespace std;

extern int yylex();
extern int yyparse();
void yyerror(char *s){
	cerr<<s<<endl;
}
extern "C"{
	int yywrap(void){
		return 1;
	}
}

%}
%start Goal
%union{
    int ival;
    char* sval;	
    Node* nval;
};

%token <ival> INTEGER
%token <sval> FUNC LABEL ID PLUS MINUS TIME DIVIDE MOD NOT AND OR LESS
 GREATER EQUAL NOTEQUAL ASSIGN LBRAC RBRAC IF GOTO CALL PARAM END RETURN VAR COLON

%type <sval> Op2 Op1 LogicalOp
%type <nval> LocalDeclaration FunctionDecl RightValue Expression GlobalList
 LocalList GlobalDeclaration Goal ParamList

%% 

Goal:	GlobalList 
		{
			cerr << "Parsing ends" << endl;
			Node* ret = new RootNode();
			ret->addChild($1);
            ret->genCode();
            ret->printCode();
			$$ = ret;
		}
		;
GlobalList:
		GlobalDeclaration GlobalList
		{
			Node* ret = new OtherNode();
			ret->addChild($1);
			ret->addChild($2);
			$$ = ret;
		}
		|
		FunctionDecl GlobalList
		{
			Node* ret = new OtherNode();
			ret->addChild($1);
			ret->addChild($2);
			$$ = ret;	
		}
		|
		/* empty */
		{
			$$ = new OtherNode();
		}
		;
GlobalDeclaration:
		VAR ID
        {
            IdNode* id = new IdNode(string($2), true);
            Node* ret = new GlobalDeclareNode(id);
            $$ = ret;
        }
        |
        VAR INTEGER ID
        {
            IdNode* id = new IdNode(string($3), true, $2);
            Node* ret = new GlobalDeclareNode(id);
            ret->addChild(id);
            $$ = ret;
        }
		;
LocalDeclaration:
		VAR ID
		{
			//node* ret = new node(DeclareNode);
			//ret->name = string($2);
			//$$ = ret;
            Node* id = new IdNode(string($2));
            Node* ret = new ExprNode(LocalDeclareType, "");
            ret->addChild(id);
            $$ = ret;
		}
		|
		VAR INTEGER ID
		{
			Node* id = new IdNode(string($3), false, $2);
            Node* ret = new ExprNode(LocalDeclareType, "");
            ret->addChild(id);
            $$ = ret;
		}
		;	
FunctionDecl:
		FUNC LBRAC INTEGER RBRAC LocalList END FUNC
		{
            Node* ret = new FuncNode($1, $3);
            ret->addChild($5);
            $$ = ret;
		}
		;
LocalList:
		Expression LocalList
		{
            Node* ret = new OtherNode();
            ret->addChild($1);
            ret->addChild($2);
            $$ = ret;
		}
		|
		LocalDeclaration LocalList
		{
            Node* ret = new OtherNode();
            ret->addChild($1);
            ret->addChild($2);
            $$ = ret;
		}
        |
        Expression
        {
            Node* ret = new OtherNode();
            ret->addChild($1);
            $$ = ret;
        }
        |
        LocalDeclaration
        {
            Node* ret = new OtherNode();
            ret->addChild($1);
            $$ = ret;
        }
		;
RightValue:
		ID
		{
			Node* ret = new IdNode(string($1));
			$$ = ret;
		}
		|
		INTEGER
		{
			Node* ret = new IdNode($1);
			$$ = ret;
		}
		;
Op2:
		PLUS | MINUS | TIME | DIVIDE | MOD | AND | OR | LESS | GREATER | EQUAL | NOTEQUAL
		;
Op1:
		MINUS | NOT
		;
LogicalOp:
		EQUAL | NOTEQUAL | LESS | GREATER | AND | OR
		;
ParamList:
        PARAM RightValue ParamList
        {
            Node* ret = new OtherNode();
            ret->addChild($2);
            ret->addChild($3);
            $$ = ret;
        }
        |
        PARAM RightValue
        {
            Node* ret = new OtherNode();
            ret->addChild($2);
            $$ = ret;
        }
        ;
Expression:
		ID ASSIGN RightValue Op2 RightValue
		{
            Node* ret = new ExprNode(Op2Type, string($4));
            Node* var = new IdNode(string($1));
            ret->addChild(var);
            ret->addChild($3);
            ret->addChild($5);
            $$ = ret;
		}
		|
		ID ASSIGN Op1 RightValue
		{
            Node* ret = new ExprNode(Op1Type, string($3));
            Node* var = new IdNode(string($1));
            ret->addChild(var);
            ret->addChild($4);
            $$ = ret;
		}
        |
		ID ASSIGN RightValue
		{
			Node* ret = new ExprNode(NoOpType, "");
            Node* var = new IdNode(string($1));
            ret->addChild(var);
            ret->addChild($3);
            $$ = ret;
		}
		|
		ID LBRAC RightValue RBRAC ASSIGN RightValue
		{
            Node* ret = new ExprNode(StoreArrayType, "");
            Node* var = new IdNode(string($1));
            ret->addChild(var);
            ret->addChild($3);
            ret->addChild($6);
            $$ = ret;
		}
		|
		ID ASSIGN ID LBRAC RightValue RBRAC
		{
            Node* ret = new ExprNode(VisitArrayType, "");
            Node* var = new IdNode(string($1));
            Node* rightValue1 = new IdNode(string($3));
            ret->addChild(var);
            ret->addChild(rightValue1);
            ret->addChild($5);
            $$ = ret;
		}
		|
		IF RightValue LogicalOp RightValue GOTO LABEL
		{
            Node* ret = new ExprNode(IfBranchType, string($3), string($6));
            ret->addChild($2);
            ret->addChild($4);
            $$ = ret;
		}
		|
		GOTO LABEL
		{
            Node* ret = new ExprNode(GotoType, "", string($2));
			$$ = ret;
		}
		|
		LABEL COLON
		{
			Node* ret = new ExprNode(LabelType, "", string($1));
            $$ = ret;
		}
		|
		ParamList ID ASSIGN CALL FUNC
		{
			Node* ret = new ExprNode(CallType, "", $5);
            Node* var = new IdNode($2);
            ret->addChild(var);
            ret->addChild($1);
            $$ = ret;            
		}
        |
        ID ASSIGN CALL FUNC
        {
            Node* ret = new ExprNode(CallType, "", $4);
            Node* var = new IdNode($1);
            ret->addChild(var);
            $$ = ret;
        }
		|
		RETURN RightValue
		{
			Node* ret = new ExprNode(ReturnType, "");
            ret->addChild($2);
			//cerr << ((IdNode*)$2)->getValue() << endl;
            $$ = ret;
		}
		;

%%
#include "lex.yy.c"
int main(int argc, char* argv[]){
	ios::sync_with_stdio();
    yyparse();
}
