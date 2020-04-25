%{
#define YYDEBUG 1
#include "decl.h"
#include <iostream>
#include <stdio.h>
using std::cout;
using std::endl;
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
%token LT LE GE GT EQ NEQ PLUS MINUS MULTIPLY DIVIDE PLUSASSG MINUSASSG MULTIPLYASSG DIVIDEASSG NOT AND OR SELFMINUS SELFPLUS
%token WHILE FOR BREAK CONTINUE RETURN IF INT FLOAT CHAR VOID LB RB LP RP LA RA COMMA SEMI ERROR
%type<ast> prog dcl func stmt assg expr_left expr funcdcl vardcl
%type<type> type
%type<para> multidim arraylist;
%type<parms> decllist parm_types parmlist
%type<set> funcbody exprlist stmtlist multidim_ind
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
prog:        dcl SEMI prog {root->lst.insert((root->lst).begin(),$1);}
            | func prog  {root->lst.insert((root->lst).begin(),$1);}
            | {root = new ast_node_prog();} ;
dcl:	       funcdcl {$$ = $1;}
            |	vardcl {$$ = $1;};
funcdcl :     type ID LP parm_types RP 
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
vardcl:      type ID arraylist decllist {
                ast_node_vardec *tmp = new ast_node_vardec();
                $3.ident = $2; 
                $3.isarray = $3.arraydim == 0? false : true;
                $4.insert($4.begin(),$3);
                tmp->type = $1;
                tmp->vars = $4;
                $$ = tmp;
            };
decllist:     COMMA ID arraylist decllist 
              {
                $3.ident = $2; 
                $3.isarray = $3.arraydim == 0? false : true;
                $4.insert($4.begin(),$3);
                $$ = $4;
              }
            | {$$ = vector<parm_type>();};
parmlist:     COMMA type ID multidim parmlist 
            {
              $4.isarray = $4.arraydim == 0? false : true;
              $4.ident = $3;
              $4.type = $2;
              $5.insert($5.begin(),$4);
              $$ = $5;
            }
            | {$$ = vector<parm_type>();};
arraylist:   LB INTCON RB arraylist {$$ = $4; $$.arraysize[$$.arraydim] = $2; ($$.arraydim)++;}
            | {$$ = parm_type(); $$.arraydim = 0;};
type:	       CHAR {$$ = T_CHAR;}
 	          |	INT {$$ = T_INT;}
            | FLOAT {$$=T_FLOAT;}
multidim:    LB RB multidim {$$ = $3; ($$.arraydim)++;}
            | {$$.arraydim=0;};
parm_types: 	VOID {$$ = vector<parm_type>();}
 	          |	type ID multidim parmlist
            {
              $3.ident = $2;
              $3.isarray = $3.arraydim == 0? false : true;
              $3.type = $1;
              $4.insert($4.begin(),$3);
              $$ = $4;
            };
funcbody:    stmt funcbody 
            {
              $2.insert($2.begin(),$1);
            $$ = $2;
            }
            | vardcl SEMI funcbody 
            {
              $3.insert($3.begin(),$1);
              $$ = $3;
            }
            | {$$ = vector<ast_node*>();};
func:	      type ID LP parm_types RP LA funcbody RA
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
exprlist:     COMMA expr exprlist{$3.insert($3.begin(),$2); $$ = $3;}
            | {$$ = vector<ast_node*>();};
stmtlist:    stmt stmtlist {$2.insert($2.begin(),$1); $$ = $2;}
            |{$$ = vector<ast_node*>();};
stmt:      	IF LP expr RP stmt ELSE stmt
            {
              ast_node_if *tmp = new ast_node_if();
              tmp->cond = $3;
              tmp->body = $5;
              tmp->el = $7;
              $$ = tmp;
            }
            | IF LP expr RP stmt %prec NO_ELSE
            {
              ast_node_if *tmp = new ast_node_if();
              tmp->cond = $3;
              tmp->body = $5;
              $$ = tmp;
            }
            |	WHILE LP expr RP stmt
            {
              ast_node_while *tmp = new ast_node_while();
              tmp->cond = $3;
              tmp->body = $5;
              $$ = tmp;
            }
            |	FOR LP assg SEMI expr SEMI assg RP stmt
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = $3;
              tmp->cond = $5;
              tmp->iter = $7;
              tmp->body = $9;
              $$ = tmp;
            }
            |	FOR LP assg SEMI expr SEMI RP stmt
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = $3;
              tmp->cond = $5;
              tmp->body = $8;
              $$ = tmp;
            }
            |	FOR LP assg SEMI SEMI assg RP stmt
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = $3;
              tmp->iter = $6;
              tmp->body = $8;
              $$ = tmp;
            }
            |	FOR LP SEMI expr SEMI assg RP stmt
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->cond = $4;
              tmp->iter = $6;
              tmp->body = $8;
              $$ = tmp;
            }
            |	FOR LP SEMI SEMI assg RP stmt
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->iter = $5;
              tmp->body = $7;
              $$ = tmp;
            }
            |	FOR LP SEMI expr SEMI RP stmt
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->cond = $4;
              tmp->body = $7;
              $$ = tmp;
            }
            |	FOR LP assg SEMI SEMI RP stmt
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->init = $3;
              tmp->body = $7;
              $$ = tmp;
            }
            |	FOR LP SEMI SEMI RP stmt 
            {
              ast_node_for *tmp = new ast_node_for();
              tmp->body = $6;
              $$ = tmp;
            }
            |	RETURN  expr  SEMI
            {
              ast_node_ret *tmp = new ast_node_ret();
              tmp->stmt = $2;
              $$ =tmp;
            }
            | RETURN  SEMI
            {
              ast_node_ret *tmp = new ast_node_ret();
              $$ =tmp;
            }
            |	LA stmtlist RA
            {
              ast_node_bigbrac *tmp = new ast_node_bigbrac();
              tmp->body = $2;
              $$ = tmp;
            }
            | expr SEMI {
              $$ = $1;
            }
            |	SEMI {}
            | BREAK
            {
              ast_node_control *tmp = new ast_node_control();
              tmp->ctrltype = C_BREAK;
              $$ = tmp;
            }
            | CONTINUE
             {
              ast_node_control *tmp = new ast_node_control();
              tmp->ctrltype = C_CONTINUE;
              $$ = tmp;
            };
multidim_ind: LB expr RB  multidim_ind {$4.push_back($2); $$ = $4;}
            | {$$ = vector<ast_node *>();};
assg:	      expr_left ASSG expr 
            {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op = O_EQ;
              $$ = tmp;
            }
            | expr_left PLUSASSG expr
            {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op = O_PLUS;
              $$ = tmp;
            }
            | expr_left MINUSASSG expr
            {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op = O_MINUS;
              $$ = tmp;
            }
            | expr_left DIVIDEASSG expr
            {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op = O_DIVIDE;
              $$ = tmp;
            }
            | expr_left MULTIPLYASSG expr
            {
              ast_node_assg *tmp = new ast_node_assg();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op = O_MULTIPLY;
              $$ = tmp;
            };
expr_left:  	ID multidim_ind
            {
                ast_node_lvalue *tmp = new ast_node_lvalue();
                tmp->id = $1;
                tmp->arrayind = $2;
                $$ = tmp; 
            };
expr:	       MINUS expr %prec UMINUS
            {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = $2;
              tmp->op = O_UMINUS;
              $$ = tmp;
            }
            |	NOT expr %prec UNOT
            {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = $2;
              tmp->op = O_UNOT;
              $$ = tmp;
            }
            |	expr PLUS expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_PLUS;
              $$ = tmp;
            }
            |	expr MINUS expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_MINUS;
              $$ = tmp;
            }
            |	expr MULTIPLY expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_MULTIPLY;
              $$ = tmp;
            }
            |	expr DIVIDE expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_DIVIDE;
              $$ = tmp;
            }
            |	expr EQ expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_EQ;
              $$ = tmp;
            }
            |	expr NEQ expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_NEQ;
              $$ = tmp;
            }
            |	expr LE expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_LE;
              $$ = tmp;
            }
            |	expr GE expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_GE;
              $$ = tmp;
            }
            |	expr GT expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_GT;
              $$ = tmp;
            }
            |	expr LT expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_LT;
              $$ = tmp;
            }
            |	expr AND expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_AND;
              $$ = tmp;
            }
            |	expr OR expr
            {
              ast_node_bin *tmp = new ast_node_bin();
              tmp->left = $1;
              tmp->right = $3;
              tmp->op =  O_OR;
              $$ = tmp;
            }
            | expr_left
            {
              $$ = $1;
            }
            |	ID LP RP
            {
              ast_node_callfunc *tmp = new ast_node_callfunc();
              tmp->id = $1;
              $$ = tmp;
            }
            | ID LP expr exprlist RP 
            {
              ast_node_callfunc *tmp = new ast_node_callfunc();
              tmp->id = $1;
              $4.insert($4.begin(),$3);
              tmp->params = $4;
              $$ = tmp;
            }
            |	assg
            {
              $$ = $1;
            }
            |	LP expr RP
            {
              $$= $2;
            }
            |	INTCON
            {
              ast_node_const *tmp = new ast_node_const();
              (tmp->data).i = $1;
              tmp->type = T_INT;
              $$ = tmp;
            }
            |	CHARCON
            {
              ast_node_const *tmp = new ast_node_const();
              (tmp->data).c = $1;
              tmp->type = T_CHAR;
              $$ = tmp;
            }
            |	FLOATCON
            {
              ast_node_const *tmp = new ast_node_const();
              (tmp->data).f = $1;
              tmp->type = T_FLOAT;
              $$ = tmp;
            }
            | expr_left SELFPLUS
            {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = $1;
              tmp->op = O_SELFPLUS;
              $$ = tmp;
            }
            | expr_left SELFMINUS 
            {
              ast_node_unary *tmp = new ast_node_unary();
              tmp->body = $1;
              tmp->op = O_SELFMINUS;
              $$ = tmp;
            };
%%
 
void yyerror(const char *s)	//当yacc遇到语法错误时，会回调yyerror函数，并且把错误信息放在参数s中
{
	cout <<s << " at line " <<yylineno << " ,lookahead token is "<< yychar<< endl;//直接输出错误信息
}

void printtokenpair(int tokentype){
  cout << "(" << yytname[tokentype-255] << ", ";
  switch(tokentype){
    case INTCON:
      cout << yylval.intcon;
      break;
    case FLOATCON:
      cout << yylval.floatcon;
      break;
    case CHARCON:
      cout << yylval.charcon;
      break;
    case ID:
      cout << yylval.id;
      break;
  }
  cout << ") ";
}
