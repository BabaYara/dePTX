all: dePTX

ptxgrammar.cc ptxgrammar.hh:
	bison -d -v -t ptxgrammar.yy -o ptxgrammar.cc

lex.ptx.cc: ptx.ll ptxgrammar.hh
	flex ptx.ll

dePTX: lex.ptx.cc ptxgrammar.cc 
	g++ dePTX.cpp $^ -lfl -o dePTX -L/opt/local/lib

clean: 
	/bin/rm -f *.tab.c *.tab.h *.yy.c dePTX
