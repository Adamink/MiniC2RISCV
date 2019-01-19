%{
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <set>
#include "node.h"
using namespace std;

int yylex();
int yyparse();
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
    node* nval;
};

%token <ival> INTEGER
%token <sval> FUNC LABEL ID PLUS MINUS TIME DIVIDE MOD NOT AND OR LESS GREATER EQUAL NOTEQUAL ASSIGN LBRAC RBRAC IF GOTO CALL PARAM END RETURN VAR COLON Error

%type <sval> Op2 Op1 LogicalOp
%type <nval> Declaration FunctionDecl RightValue Expression GlobalList LocalList GlobalDeclaration Goal

%% 

Goal:	GlobalList 
		{
			node* ret = new node(RootNode);
			ret->add_child($1);
			ret->adjust_child();
			ret->set_table();
			ret->all_allo_reg();
			ret->all_gen_code();
			$$ = ret;
		}
		;
GlobalList:
		GlobalDeclaration GlobalList
		{
			node* ret = new node(GlobalListNode);
			ret->add_child($1);
			ret->add_child($2);
			$$ = ret;
		}
		|
		FunctionDecl GlobalList
		{
			node* ret = new node(GlobalListNode);
			ret->add_child($1);
			ret->add_child($2);
			$$ = ret;	
		}
		|
		/* empty */
		{
			$$ = new node(GlobalListNode);
		}
		;
GlobalDeclaration:
		Declaration
		{
			$1->type = GlobalDeclareNode;
			$$ = $1;
		}
		;
Declaration:
		VAR ID
		{
			node* ret = new node(DeclareNode);
			ret->name = string($2);
			$$ = ret;
		}
		|
		VAR INTEGER ID
		{
			node* ret = new node(DeclareNode);
			ret->name = string($3);
			ret->length = $2;
			ret->isArray = true;
			$$ = ret;
		}
		;	
FunctionDecl:
		FUNC LBRAC INTEGER RBRAC LocalList END FUNC
		{
			node* ret = new node(FuncNode);
			ret->paraNum = $3;
			ret->name = string($1);
			ret->add_child($5);
			$$ = ret;
		}
		;
LocalList:
		Expression LocalList
		{
			node* ret = new node(ExprListNode);
			ret->add_child($1);
			ret->add_child($2);
			$$ = ret;
		}
		|
		Declaration LocalList
		{
			node* ret = new node(ExprListNode);
			ret->add_child($1);
			ret->add_child($2);
			$$ = ret;
		}
		|
		/* empty */
		{
			$$ = new node(ExprListNode);
		}
		;
RightValue:
		ID
		{
			node* ret = new node(IDNode);
			ret->name = string($1);
			$$ = ret;
		}
		|
		INTEGER
		{
			node* ret = new node(IntNode);
			ret->name = to_string($1);
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
Expression:
		ID ASSIGN RightValue Op2 RightValue
		{
			node* ret = new node(0);

			node* idnode = new node(IDNode);
			idnode->name = string($1);
			node* opnode = new node(OpNode);
			opnode->name = string($4);

			ret->add_child(idnode);
			ret->add_child($3);
			ret->add_child(opnode);
			ret->add_child($5);

			$$ = ret;
		}
		|
		ID ASSIGN Op1 RightValue
		{
			node* ret = new node(1);

			node* idnode = new node(IDNode);
			idnode->name = string($1);
			node* opnode = new node(OpNode);
			opnode->name = string($3);

			ret->add_child(idnode);
			ret->add_child(opnode);
			ret->add_child($4);

			$$ = ret;			
		}
		|
		ID LBRAC RightValue RBRAC ASSIGN RightValue
		{
			node* ret = new node(2);

			node* idnode = new node(IDNode);
			idnode->name = string($1);

			ret->add_child(idnode);
			ret->add_child($3);
			ret->add_child($6);

			$$ = ret;		
		}
		|
		ID ASSIGN ID LBRAC RightValue RBRAC
		{
			node* ret = new node(3);

			node* id1node= new node(IDNode);
			id1node->name = string($1);
			node* id2node = new node(IDNode);
			id2node->name = string($3);

			ret->add_child(id1node);
			ret->add_child(id2node);
			ret->add_child($5);

			$$ = ret;
		}
		|
		IF RightValue LogicalOp RightValue GOTO LABEL
		{
			node* ret = new node(4);

			node* opnode = new node(OpNode);
			opnode->name = string($3);

			ret->name = string($6);

			ret->add_child($2);
			ret->add_child(opnode);
			ret->add_child($4);
			
			$$ = ret;
		}
		|
		GOTO LABEL
		{
			node* ret = new node(5);
			ret->name = string($2);
			$$ = ret;
		}
		|
		LABEL COLON
		{
			node* ret = new node(6);
			ret->name = string($1);
			$$ = ret;
		}
		|
		PARAM RightValue
		{
			node* ret = new node(7);
			ret->add_child($2);
			$$ = ret;
		}
		|
		ID ASSIGN CALL FUNC
		{
			node* ret = new node(8);
			node* idnode = new node(IDNode);
			idnode->name = string($1);
			ret->add_child(idnode);
			ret->name = string($4);
			$$ = ret;
		}
		|
		RETURN RightValue
		{
			node* ret = new node(9);
			ret->add_child($2);
			$$ = ret;
		}
		|
		CALL FUNC
		{
			node* ret = new node(10);
			ret->name = string($2);
			$$ = ret;
		}
		|
		ID ASSIGN RightValue
		{
			node* ret = new node(11);
			node* idnode = new node(IDNode);
			idnode->name = string($1);
			ret->add_child(idnode);
			ret->add_child($3);
			$$ = ret;
		}
		;

%%
#include "lex.cc"
int main(int argc, char* argv[]){
	init_reg();
	ios::sync_with_stdio();
#ifdef LOCAL
	FILE* inputFile;
	if(argc==1){
		inputFile = fopen("input.c", "r");
	}
	else{
		inputFile = fopen(argv[1], "r");
		outputFile = fopen(argv[2], "wb");
	}
	if (!inputFile) {
		printf("I can't open input file!");
		return -1;
	}
	yyin = inputFile;
	yyout = outputFile;
#endif
    yyparse();
}
