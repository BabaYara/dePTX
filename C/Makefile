all: dePTX

parse.tab.c parse.tab.h: parse.y
	bison -d -v -t parse.y

lex.yy.c: lex.l parse.tab.h
	flex lex.l

dePTX: lex.yy.c parse.tab.c parse.tab.h
	g++ dePTX.cpp parse.tab.c lex.yy.c -lfl -o dePTX -L/opt/local/lib -DYYMAXDEPTH=1000000

clean: 
	/bin/rm -f *.tab.c *.tab.h *.yy.c dePTX
