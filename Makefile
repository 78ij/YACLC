all:
	bison -v -d YACL.y  && flex --wincompat YACL.l  && g++ lex.yy.c YACL.tab.c -o parser -std=gnu++11
clean:
	rm *.yy.c *.exe *.tab.c *.tab.h *.output *.out