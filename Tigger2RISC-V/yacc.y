%{
#include <iostream>
#include <sstream>
#include <cassert>
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
stringstream inputFile;
%}
%start Goal
%union{
    int ival;
    char* sval;	
    Node* nval;
};

%token <ival> INTEGER PLUS MINUS TIME DIVIDE MOD NOT AND OR LESS GREATER EQUAL NOTEQUAL ASSIGN LBRAC RBRAC IF GOTO CALL END STORE LOADADDR LOAD MALLOC RETURN COLON
%token <sval> FUNC LABEL VARIABLE REG
%type <ival> Op2 Op1 LogicalOp
%type <nval> Goal GlobalList GlobalVarDecl FunctionDecl ExprList Expression 

%% 

Goal:	GlobalList 
		{
			Node* ret = new Node();
			ret->addChild($1);
            ret->fillReturnNode();
            ret->printAllCode();
            cerr << inputFile.str();
			$$ = ret;
		}
		;
GlobalList:
        FunctionDecl GlobalList
        {
            Node* ret = new Node();
            ret->addChild($1);
            ret->addChild($2);
            $$ = ret;
        }
        |
        GlobalVarDecl GlobalList
        {
            Node* ret = new Node();
            ret->addChild($1);
            ret->addChild($2);
            $$ = ret;
        }
        |
        /* empty */
        {
            $$ = new Node(EmptyType);
        }
        ;
GlobalVarDecl:
        VARIABLE ASSIGN INTEGER
        {
            Node* ret = new Node();
            stringstream code;
            code << "\t.global\t" << $1 << "\n\t.section\t.sdata\n\t.align\t2\n\t.type\t" << $1<<",@object\n\t.size\t"<< $1 << ",4\n" << $1 << ":\n\t.word\t" << $3 << endl;
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        VARIABLE ASSIGN MALLOC INTEGER
        {
            Node* ret = new Node();
            stringstream code;
            code << "\t.comm\t" << $1 << "," << 4 * $4 << ",4" << endl;
            ret->appendCode(code.str());
            $$ = ret;
        }
        ;
FunctionDecl:
        FUNC LBRAC INTEGER RBRAC LBRAC INTEGER RBRAC ExprList END FUNC
        {
            int stk = ($6 / 4 + 1) * 16;
            stringstream codeBeforeChildren;
            if(strcmp($1,"main")==0){
                codeBeforeChildren << "\t.text\n\t.align\t2\n\t.global\t" << $1 << "\n\t.type\t" << $1 << ",@function\n" << $1 << ":\n\tadd\tsp,sp," << -stk <<"\n\tsw\tra," << stk-4 << "(sp)" << endl;
            }
            else{
                codeBeforeChildren << 
                "\t.size\t" << $1 << ",.-" << $1 << "\n"
                << "\t.text\n\t.align\t2\n\t.global\t" << $1 << "\n\t.type\t" << $1 << ",@function\n" << $1 << ":\n\tadd\tsp,sp," << -stk <<"\n\tsw\tra," << stk-4 << "(sp)" << endl;
            }


            stringstream codeAfterChildren;
            codeAfterChildren << "\t.size\t" << $1 << ",.-" << $1 << endl;
            Node* ret = new Node(FuncType);
            ret->setStackSize(stk);
            ret->appendCodeBeforeChildren(codeBeforeChildren.str());
            ret->appendCodeAfterChildren(codeAfterChildren.str());
            ret->addChild($8);
            $$ = ret;
        }
        ;
ExprList:
        Expression ExprList
        {
            Node* ret = new Node();
            ret->addChild($1);
            ret->addChild($2);
            $$ = ret;
        }
        |
        /* empty */
        {
            $$ = new Node(EmptyType);
        }
        ;
Expression:
        REG ASSIGN REG Op2 REG
        {
            string opAsm;
            string firstSentence;
            string secondSentence;
            switch($4){
                case PLUS:
                    opAsm = string("add");
                    break;
                case MINUS:
                    opAsm = string("sub");
                    break;
                case TIME:
                    opAsm = string("mul");
                    break;
                case DIVIDE:
                    opAsm = string("div");
                    break;
                case MOD:
                    opAsm = string("rem");
                    break;
                case LESS:
                    opAsm = string("slt");
                    break;
                case GREATER:
                    opAsm = string("sgt");
                    break;
                case AND:
                    opAsm = string("and");
                    secondSentence = "\t" + string("snez\t") + $1 + "," + $1 + "\n"; 
                    break;
                case OR:
                    opAsm = string("or");
                    secondSentence = "\t" + string("snez\t") + $1 + "," + $1 + "\n"; 
                    break;
                case EQUAL:
                    opAsm = string("xor");
                    secondSentence = "\t" + string("seqz\t") + $1 + "," + $1 + "\n"; 
                    break;
                case NOTEQUAL:
                    opAsm = string("xor");
                    secondSentence = "\t" + string("snez\t") + $1 + "," + $1 + "\n";
                    break;
                default:
                    assert(false);
            }
            firstSentence = "\t" + opAsm + "\t" + $1 + "," + $3 + "," + $5 + "\n";
            Node* ret = new Node();
            ret->appendCode(firstSentence + secondSentence);
            $$ = ret;
        }
        |
        REG ASSIGN REG Op2 INTEGER
        {
            string opAsm;
            if($4==LESS)
                opAsm = string("slti");
            else if($4==PLUS) // warning!
                opAsm = string("add");
            stringstream code;
            code << "\t" + opAsm + "\t" + $1 + "," + $3 + ","  << $5 << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        } 
        |
        REG ASSIGN Op1 REG
        {
            string opAsm;
            if($3==NOT)
                opAsm = string("not");
            else if($3==MINUS)
                opAsm = string("neg");
            stringstream code;
            code <<"\t" << opAsm << "\t" << $1 << "," << $4 << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        REG ASSIGN REG
        {
            stringstream code;
            code << "\tmv\t" << $1 << "," << $3 << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        REG ASSIGN INTEGER
        {
            stringstream code;
            code << "\tli\t" << $1 <<"," << $3 << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        REG LBRAC INTEGER RBRAC ASSIGN REG
        {
            stringstream code;
            code << "\tsw\t" << $6 << "," << $3 << "(" << $1 << ")" << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());    
            $$ = ret;
        }
        |
        REG ASSIGN REG LBRAC INTEGER RBRAC
        {
            stringstream code;
            code << "\tlw\t" << $1 << "," << $5 << "(" << $3 << ")" <<endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        IF REG LogicalOp REG GOTO LABEL
        {
            string opAsm;
            string preface;
            switch($3){
                case EQUAL:
                    opAsm = "beq";
                    break;
                case NOTEQUAL:
                    opAsm = "bne";
                    break;
                case LESS:
                    opAsm = "blt";
                    break;
                case GREATER:
                    opAsm = "bgt";
                    break;
                case AND:
                    opAsm = "bnez";
                    cerr << "&& appears in if-goto" << endl;
                    assert(false);
                    break;
                case OR:
                    opAsm = "bnez";
                    cerr << "|| appears in if-goto" << endl;
                    assert(false);
                    break;
            }
            stringstream code;
            code << "\t" << opAsm << "\t" << $2 << "," << $4 << ",." << $6 <<endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        GOTO LABEL 
        {
            stringstream code;
            code << "\tj\t." << $2 << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        LABEL COLON
        {
            stringstream code;
            code << "." << $1 << ":"<<endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        CALL FUNC
        {
            stringstream code;
            code << "\tcall\t" << $2 << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;  
        }
        |
        STORE REG INTEGER
        {
            stringstream code;
            code << "\tsw\t" << $2 <<"," << 4*$3 << "(sp)" << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        LOAD INTEGER REG
        {
            stringstream code;
            code << "\tlw\t" << $3 <<"," << 4*$2 << "(sp)" << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        LOAD VARIABLE REG
        {
            stringstream code;
            code << "\tlui\t" << $3 << ",%hi(" << $2 << ")" << endl;
            code << "\tlw\t" << $3 << ",%lo(" << $2 << ")(" << $3 <<")" <<endl;  
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        LOADADDR INTEGER REG
        {
            stringstream code;
            code << "\tadd\t" << $3 <<",sp," << 4*$2 << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        LOADADDR VARIABLE REG
        {
            stringstream code;
            code << "\tlui\t" << $3 <<",%hi(" << $2 << ")" << endl;
            code << "\tadd\t" << $3 << "," << $3 << ",%lo(" << $2 << ")" << endl;
            Node* ret = new Node();
            ret->appendCode(code.str());
            $$ = ret;
        }
        |
        RETURN
        {
            Node* ret = new Node(ReturnType);
            $$ = ret;
        }
        ;
Op2:    PLUS | MINUS | TIME | DIVIDE | MOD | LESS | GREATER | AND | OR | EQUAL | NOTEQUAL
        ;
Op1:    MINUS | NOT
        ;
LogicalOp:
		EQUAL | NOTEQUAL | LESS | GREATER | AND | OR
		;
%%
#include "lex.cc"
int main(int argc, char* argv[]){
    yyparse();
}
