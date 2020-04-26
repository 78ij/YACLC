#include "getopt.h"
#include <iostream>
#include "decl.h"
#include <cstdio>
#include "semantic.h"
#include <vector>
using std::cout;
using std::endl;
using std::cerr;
using std::fopen;
using std::fclose;
using std::vector;
extern int yyparse();
extern int yylex();
using std::cout;
using std::endl;
extern ast_node_prog *root;
void printhelp(){
    cout << "YACLC - Yet Another C-like Language Compiler.\n";
    cout << "Usage: YACLC.exe [options] file\n";
    cout << "Options:\n";
    cout << "-h, Print this help message.\n";
    cout << "-l, Print lexer output (a stream of tokens).\n";
    cout << "-a, Print parser output (an abstract syntax tree).\n";
}
int main(int argc,char **argv){ 
    if(argc == 1){
        printhelp();
        return 0;
    } 
    char ch;
    bool lexer;
    bool ast;
    while((ch = getopt(argc,argv,"hla")) != -1){
        switch(ch){
            case 'h':
                printhelp();
                return 0;
            case 'l' :
                lexer = true;
                break;
            case 'a':
                ast = true;
                break;
        }
    }
    if(optind >= argc){
        cout << "No input file!\n";
        return -1;
    } 
	FILE* fp=fopen(argv[optind], "r");
	if(fp==NULL)
	{
		cout << "Cannot open " << argv[optind];
		return -1;
	}
	extern FILE* yyin;	
	yyin=fp;
    int t;
    if(lexer){
        cout << "----------------------------Begin Token Stream -----------------------------\n";
        while(t = yylex()){
            printtokenpair(t);
            cout << endl;
        }
        cout << "----------------------------End Token Stream -------------------------------\n";
    }
    fseek(yyin,0,0);
    yyparse();
    fclose(fp);
    if(ast){
        cout << "----------------------------Begin AST---------------------------------------\n";
        root->print(0);
        cout << "----------------------------End AST-----------------------------------------\n";
    }
    Semantic s(root,true);
    s.analysis();
	return 0;
}

