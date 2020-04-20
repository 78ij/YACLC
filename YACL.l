
%{
#include <stdio.h> 
//RELOP
#define LT					        1 
#define	LE				        	2
#define GT				        	3
#define	GE			        		4
#define	EQ			        		5
#define NE			        		6

//BINOP
#define PLUS                7
#define MINUS               8
#define MULTIPLY            9
#define DIVIDE              10

//ASSGOP
#define PLUSASSG            11
#define MINUSASSG           12
#define MULTIPLYASSG        13
#define DIVIDEASSG          14
#define ASSG                15

//LogicalOP
#define AND                 16
#define OR                  17

//SELFOP
#define SELFPLUS            18
#define SELFMINUS           19

//Keyword
#define WHILE			        	20
#define	FOR				        	21
#define	BREAK		      	    22
#define	CONTINUE	      		23
#define	RETURN		    	    24
#define IF                  25

//TYPE
#define INT                 26        
#define FLOAT               27
#define CHAR                28
#define VOID                29
//ID
#define ID                  30

//LITERAL
#define INTCON              31
#define CHARCON             32
#define FLOATCON            33

//DELIMITER
//[],(),{}
#define LB                  34    
#define RB                  35
#define LP                  36
#define RP                  37
#define LA                  38
#define RA                  39
#define COMMA               40
#define SEMI                41

#define ERRORCHAR           42

const char* Nodenames[] = {
"LT",					         
"LE",				        	
"GT",				        	
"GE",			        		
"EQ",			        		
"NE",			        		
"PLUS",                
"MINUS",               
"MULTIPLY",
"DIVIDE",
"PLUSASSG",
"MINUSASSG",
"MULTIPLYASSG",
"DIVIDEASSG",
"ASSG",
"AND",
"OR",
"SELFPLUS",
"SELFMINUS",
"WHILE",
"FOR",
"BREAK",
"CONTINUE",
"RETURN",
"IF",
"INT",
"FLOAT",
"CHAR",
"VOID",
"ID",
"INTCON",
"CHARCON",
"FLOATCON",
"LB",
"RB",
"LP",
"RP",
"LA",
"RA",
"COMMA",
"SEMI",
"ERRORCHAR",
};
int yylval;
%}

delim       [" " \t \n]*
letter	    [A-Za-z_]
digit       [0-9]
id          [a-zA-Z]([a-zA-Z]|[0-9]|_)*
intcon      [1-9][0-9]*
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
<INITIAL>return            {return (RETURN);}
<INITIAL>break             {return (BREAK);}
<INITIAL>continue          {return (CONTINUE);}

<INITIAL>"<"	             {return LT; }
<INITIAL>"<="	             {return LE; }
<INITIAL>"=="	             {return EQ; }
<INITIAL>"!="	             {return NE; }
<INITIAL>">"	             {return GT; }
<INITIAL>">="	             {return GE; }

<INITIAL>"+"               {return PLUS; }
<INITIAL>"-"               {return MINUS; }
<INITIAL>"*"               {return MULTIPLY; }
<INITIAL>"/"               {return DIVIDE; }

<INITIAL>"="               {return ASSG; }
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

<INITIAL>{id}	             {return (ID);}
<INITIAL>{intcon}	         {return (INTCON);}
<INITIAL>{charcon}         {return(CHARCON);}
<INITIAL>{floatcon}        {return(FLOATCON);}
<INITIAL>.                 {return(ERRORCHAR);}
%%
int yywrap (){
  return 1;
}
void print(int val,int value){
  printf("(%s,%d) ",Nodenames[val],value);
}
int main (int argc, char ** argv){
    int a;
	  while(a = yylex()){
      print(a-1,0);
    }
}