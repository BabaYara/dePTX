all: dePTX

ptxgrammar.cc : ptxgrammar.yy
	bison -d  ptxgrammar.yy -o ptxgrammar.cc

ptx.cc: ptx.ll ptxgrammar.cc
	flex -t ptx.ll > ptx.cc

%.o: %.cpp
	g++ -c -O3 $< -o $@ -I/opt/local/include -Werror -Wall

%.o: %.cc
	g++ -c -O3 $< -o $@ -I/opt/local/include -Werror -Wall

OBJ= PTXLexer.o \
		 PTXParser.o \
	   ptx.o \
		 ptxgrammar.o \
		 dePTX.o 

dePTX: $(OBJ)
	g++ $^ -lfl -o dePTX -L/opt/local/lib -I/opt/local/include 

clean: 
	/bin/rm -f ptx.cc ptxgrammar.cc ptxgrammar.hh  dePTX $(OBJ)

$(OBJ): ptx.cc ptxgrammar.cc PTXLexer.h PTXParser.h
