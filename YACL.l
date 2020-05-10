
%{
  
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include<vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <malloc.h>
class ast_node;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::strcpy;
enum types{
  T_INT,
  T_FLOAT,
  T_CHAR,
  T_INTARRAY,
  T_FLOATARRAY,
  T_CHARARRAY,
  T_VOID
};
struct parm_type {
  bool isarray;
  int arraydim;
  int arraysize[10];
  string ident;
  types type;
};

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
#include "YACL.tab.h" 
%}
%option yylineno
delim       [" " \t \n]*
letter	    [A-Za-z_]
digit       [0-9]
id          [a-zA-Z]([a-zA-Z]|[0-9]|_)*
intcon      0|([1-9][0-9]*)
charcon     '([a-zA-Z]|[0-9]|\\n|\\0)'
floatcon    [0-9]*\.?[0-9]?([eE][-+]?[0-9]+)?
%s COMMENT
%s COMMENT2
%%

<INITIAL>"/*"              {BEGIN COMMENT;}
<COMMENT>"*/"              {BEGIN INITIAL;}
<COMMENT>.|\n              {;}
<INITIAL>"//"              {BEGIN COMMENT2;}
<COMMENT2>\n               {BEGIN INITIAL;}
<COMMENT2>.	               {;}

<INITIAL>{delim}           {;}
<INITIAL>while	           {return (WHILE);}
<INITIAL>for    	         {return (FOR);}
<INITIAL>int    	         {return (INT);}
<INITIAL>char    	         {return (CHAR);}
<INITIAL>float    	       {return (FLOAT);}
<INITIAL>void              {return (VOID);}
<INITIAL>if                {return (IF);}
<INITIAL>else              {return (ELSE);}
<INITIAL>return            {return (RETURN);}
<INITIAL>break             {return (BREAK);}
<INITIAL>continue          {return (CONTINUE);}

<INITIAL>"<"	             {return LT; }
<INITIAL>"<="	             {return LE; }
<INITIAL>"=="	             {return EQ; }
<INITIAL>"!="	             {return NEQ; }
<INITIAL>">"	             {return GT; }
<INITIAL>">="	             {return GE; }

<INITIAL>"+"               {return PLUS; }
<INITIAL>"-"               {return MINUS; }
<INITIAL>"*"               {return MULTIPLY; }
<INITIAL>"/"               {return DIVIDE; }

<INITIAL>"="               {return ASSG;}
<INITIAL>"+="              {return PLUSASSG; }
<INITIAL>"-="              {return MINUSASSG; }
<INITIAL>"/="              {return DIVIDEASSG; }
<INITIAL>"*="              {return MULTIPLYASSG; }

<INITIAL>"&&"              {return AND; }
<INITIAL>"||"              {return OR; }
<INITIAL>"++"              {return SELFPLUS; }
<INITIAL>"--"              {return SELFMINUS; }

<INITIAL>"("               {return LP; }
<INITIAL>")"               {return RP; }
<INITIAL>"["               {return LB; }
<INITIAL>"]"               {return RB; }
<INITIAL>"{"               {return LA; }
<INITIAL>"}"               {return RA; }
<INITIAL>","               {return COMMA; }
<INITIAL>";"               {return SEMI; }

<INITIAL>{id}	             {
  yylval.id = string(yytext);
  return (ID);}
<INITIAL>{intcon}	         {yylval.intcon = std::atoi(yytext);return (INTCON); }
<INITIAL>{charcon}         {yylval.charcon = yytext[0]; return(CHARCON);}
<INITIAL>{floatcon}        {yylval.floatcon = atof(yytext); return(FLOATCON);}
<INITIAL>.                 {cout << "line " << yylineno << ": Lexical Analysis ERROR\n";exit(0); return ERROR;}
%%
int yywrap (){
  return 1;
}

void eat_to_newline(void)
{
    int c;
	c= getc(yyin);
    while (c != EOF && c != '\n' && c != '\0')
	c = getc(yyin)
        ;
}