
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

%%
{delim}           {;}
while	            {return (WHILE);}
for    	          {return (FOR);}
int    	          {return (INT);}
char    	        {return (CHAR);}
float    	        {return (FLOAT);}
void              {return (VOID);}
if                {return (IF);}
return            {return (RETURN);}
break             {return (BREAK);}
continue          {return (CONTINUE);}

"<"	              {return LT; }
"<="	            {return LE; }
"=="	            {return EQ; }
"!="	            {return NE; }
">"	              {return GT; }
">="	            {return GE; }

"+"               {return PLUS; }
"-"               {return MINUS; }
"*"               {return MULTIPLY; }
"/"               {return DIVIDE; }

"="               {return ASSG; }
"+="              {return PLUSASSG; }
"-="              {return MINUSASSG; }
"/="              {return DIVIDEASSG; }
"*="              {return MULTIPLYASSG; }

"&&"              {return AND; }
"||"              {return OR; }
"++"              {return SELFPLUS; }
"--"              {return SELFMINUS; }

"("               {return LP; }
")"               {return RP; }
"["               {return LB; }
"]"               {return RB; }
"{"               {return LA; }
"}"               {return RA; }
","               {return COMMA; }
";"               {return SEMI; }

{id}	            {return (ID);}
{intcon}	        {return (INTCON);}
{charcon}         {return(CHARCON);}
{floatcon}        {return(FLOATCON);}
.                 {return(ERRORCHAR);}
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
      print(a-1);
    }
}