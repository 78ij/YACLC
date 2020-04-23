%{
#define YYDEBUG 1
#include "decl.hpp"
#include <iostream>
#include <cstdio>
#include<vector>
using std::cout;
using std::endl;
using std::cerr;
using std::fopen;
using std::fclose;
using std::vector;
void yyerror(const char *s);
extern int yylex(void);
extern int yylineno;
ast_node_prog *root;
struct yt {
  vector<ast_node*> set;
  vector<parm_type> parms;
  parm_type para;
  int dims;
  types type;
  ast_node * ast;
  float floatcon;
  int intcon;
  char charcon;
  /* which operator to use (for relational and equality operators). */
  string id;
  //struct symbol_node * symbol;
};
#define YYSTYPE yt
%}
 

%locations 
%token<intcon>INTCON
%token<charcon>CHARCON
%token<floatcon>FLOATCON
%token<id>ID
%token LT LE GE GT EQ NE PLUS MINUS MULTIPLY DIVIDE PLUSASSG MINUSASSG MULTIPLYASSG DIVIDEASSG NOT AND OR SELFMINUS SELFPLUS
%token WHILE FOR BREAK CONTINUE RETURN IF INT FLOAT CHAR VOID LB RB LP RP LA RA COMMA SEMI ERROR
%type<ast> prog dcl func stmt assg expr_left expr funcdcl vardcl
%type<type> type
%type<para> multidim arraylist;
%type<parms> decllist parm_types parmlist
%type<set> funcbody exprlist stmtlist
%nonassoc NO_ELSE
%nonassoc ELSE

%left COMMA

%left AND OR

%right ASSG
%right PLUSASSG
%right MINUSASSG
%right MULTIPLYASSG
%right DIVIDEASSG
 
%left GT GE LT LE 
%left EQ NEQ
%left PLUS MINUS
%left MULTIPLY DIVIDE

%left SELFPLUS SELFMINUS
%right UMINUS
%right UNOT

%%
prog	      : dcl SEMI prog {root->lst.push_back($1);}
            | func prog  {root->lst.push_back($1);}
            | {root = new ast_node_prog();} ;
dcl	        :	funcdcl {$$ = $1;}
            |	vardcl {$$ = $1;};
funcdcl     : type ID LP parm_types RP 
              {
                ast_node_funcdec *tmp = new ast_node_funcdec();
                tmp->type = $1;
                tmp->id = $2;
                tmp->parms = $4;
                $$=tmp;
              }
            |	VOID ID LP parm_types RP
             {
                ast_node_funcdec *tmp = new ast_node_funcdec();
                tmp->type = T_VOID;
                tmp->id = $2;
                tmp->parms = $4;
                $$=tmp;
              }
            ;
vardcl      : type ID arraylist decllist {
                ast_node_vardec *tmp = new ast_node_vardec();
                $3.ident = $2; 
                $3.isarray = $3.arraydim == 0? false : true;
                $4.push_back($3);
                tmp->type = $1;
                tmp->vars = $4;
                $$ = tmp;
            };
decllist    : COMMA ID arraylist decllist 
              {
                $3.ident = $2; 
                $3.isarray = $3.arraydim == 0? false : true;
                $4.push_back($3);
                $$ = $4;
              }
            | {$$ = vector<parm_type>();};
parmlist    : COMMA type ID multidim parmlist 
            {
              $4.isarray = $4.arraydim == 0? false : true;
              $4.ident = $3;
              $4.type = $2;
              $5.push_back($4);
              $$ = $5;
            }
            | {$$ = vector<parm_type>();};
arraylist   : LB INTCON RB arraylist {$$ = $4; $$.arraysize[$$.arraydim] = $2; ($$.arraydim)++;}
            | {$$ = parm_type(); $$.arraydim = 0;};
type	      :	CHAR {$$ = T_CHAR;}
 	          |	INT {$$ = T_INT;}
            | FLOAT {$$=T_FLOAT;}
multidim    : LB RB multidim {$$ = $3; ($$.arraydim)++;}
            | {$$.arraydim=0;};
parm_types	:	VOID {$$ = vector<parm_type>();}
 	          |	type ID multidim parmlist
            {
              $3.ident = $2;
              $3.isarray = $3.arraydim == 0? false : true;
              $3.type = $1;
              $4.push_back($3);
              $$ = $4;
            };
funcbody    : stmt funcbody 
            {
              $2.push_back($1);
            $$ = $2;
            }
            | vardcl SEMI funcbody 
            {
              $3.push_back($1);
              $$ = $3;
            }
            | {$$ = vector<ast_node*>();};
func	      :	type ID LP parm_types RP LA funcbody RA
            {
                ast_node_funcdef *tmp = new ast_node_funcdef();
               tmp->ret = $1;
               tmp->id = $2;
               tmp->body = $7;
               tmp->parms = $4;
               $$ = tmp;
            }
 	          |	VOID ID LP parm_types RP LA funcbody RA 
             {
               ast_node_funcdef *tmp = new ast_node_funcdef();
               tmp->ret = T_VOID;
               tmp->id = $2;
               tmp->body = $7;
               tmp->parms = $4;
               $$ = tmp;
             };
exprlist    : COMMA expr exprlist{$3.push_back($2); $$ = $3;}
            | {$$ = vector<ast_node*>();};
stmtlist    : stmt stmtlist {$2.push_back($1); $$ = $2;}
            |{$$ = vector<ast_node*>();};
stmt	      :	IF LP expr RP stmt ELSE stmt
            | IF LP expr RP stmt
            |	WHILE LP expr RP stmt
            |	FOR LP assg SEMI expr SEMI assg RP stmt
            |	FOR LP assg SEMI expr SEMI RP stmt
            |	FOR LP assg SEMI SEMI assg RP stmt
            |	FOR LP SEMI expr SEMI assg RP stmt
            |	FOR LP SEMI SEMI assg RP stmt
            |	FOR LP SEMI expr SEMI RP stmt
            |	FOR LP assg SEMI SEMI RP stmt
            |	FOR LP SEMI SEMI RP stmt 
            |	RETURN  expr  SEMI
            | RETURN  SEMI
            |	assg SEMI
            |	ID LP RP SEMI
            | ID LP expr exprlist RP SEMI
            |	LA stmtlist RA
            |	SEMI
            | BREAK
            | CONTINUE;
multidim_ind: LB expr RB  multidim_ind 
            |;
assg	      :	ID multidim_ind ASSG expr
            | ID multidim_ind PLUSASSG expr
            | ID multidim_ind MINUSASSG expr
            | ID multidim_ind DIVIDEASSG expr
            | ID multidim_ind MULTIPLYASSG expr;
expr_left   :	ID multidim_ind;
expr	      :	MINUS expr %prec UMINUS;
            |	NOT expr %prec UNOT
            |	expr PLUS expr
            |	expr MINUS expr
            |	expr MULTIPLY expr
            |	expr DIVIDE expr
            |	expr EQ expr
            |	expr NEQ expr
            |	expr LE expr
            |	expr GE expr
            |	expr GT expr
            |	expr LT expr
            |	expr AND expr
            |	expr OR expr
            | expr_left
            | ID LP expr exprlist RP 
            |	LP expr RP
            |	INTCON
            |	CHARCON
            |	FLOATCON
            | expr_left SELFPLUS
            | expr_left SELFMINUS ;
%%
 
void yyerror(const char *s)	//当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	cerr<<s<<yylineno << " "<< yychar<< endl;//直接输出错误信息
}
 
int main()//程序主函数，这个函数也可以放到其它.c, .cpp文件里


{ 
  yydebug = 1;
FILE *stream = freopen( "freopen.out", "w", stderr );
	const char* sFile="test.yacs";//打开要读取的文本文件
	FILE* fp=fopen(sFile, "r");
	if(fp==NULL)
	{
		cout << "cannot open " << sFile;
		return -1;
	}
	extern FILE* yyin;	//yyin和yyout都是FILE*类型
	yyin=fp;//yacc会从yyin读取输入，yyin默认是标准输入，这里改为磁盘文件。yacc默认向yyout输出，可修改yyout改变输出目的
 
	cout << "-----begin parsing"  << sFile <<endl;;
	yyparse();//使yacc开始读取输入和解析，它会调用lex的yylex()读取记号
	cout << "-----end parsing" << endl;
  
	fclose(fp);
  root->print(0);
  fclose(stream);
	return 0;
}

