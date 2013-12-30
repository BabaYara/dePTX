all: dePTX

ptxgrammar.cpp : ptxgrammar.yy
	bison -d  ptxgrammar.yy -o ptxgrammar.cpp

ptx.cpp: ptx.ll ptxgrammar.cpp
	flex -t ptx.ll > ptx.cpp

%.o: %.cpp
	g++ -c -O3 $< -o $@ -I/opt/local/include

OBJ= PTXLexer.o \
	   ptx.o \
		 ptxgrammar.o \
		 dePTX.o 

dePTX: $(OBJ)
	g++ $^ -lfl -o dePTX -L/opt/local/lib -I/opt/local/include

clean: 
	/bin/rm -f ptx.cpp ptxgrammar.cpp  dePTX $(OBJ)

$(OBJ): ptx.cpp ptxgrammar.cpp PTXLexer.h PTXParser.h
