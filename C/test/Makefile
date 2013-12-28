all: snazzle

snazzle.tab.c snazzle.tab.h: snazzle.y
	bison -d snazzle.y

lex.yy.c: snazzle.l snazzle.tab.h
	flex snazzle.l

snazzle: lex.yy.c snazzle.tab.c snazzle.tab.h
	g++ snazzle.tab.c lex.yy.c -lfl -o snazzle -L/opt/local/lib

clean: 
	/bin/rm -f *.tab.c *.tab.h *.yy.c snazzle
