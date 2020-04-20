all:
	flex YACL.l && gcc lex.yy.c
clean:
	rm *.yy.c *.exe