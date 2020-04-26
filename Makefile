all:
	bison -v -d YACL.y  && flex --wincompat YACL.l  && g++ lex.yy.c YACL.tab.c main.cpp decl.cpp semantic.cpp -o YACLC -std=gnu++11
clean:
	rm *.yy.c *.exe *.tab.c *.tab.h *.output *.out