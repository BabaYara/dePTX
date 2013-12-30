all: dePTX

ptxgrammar.cpp ptxgrammar.hpp: ptxgrammar.yy
	bison -d  ptxgrammar.yy -o ptxgrammar.cpp

ptx.cpp: ptx.ll ptxgrammar.hpp
	flex -t ptx.ll > ptx.cpp

dePTX: ptx.cpp ptxgrammar.cpp
	g++ dePTX.cpp $^ -lfl -o dePTX -L/opt/local/lib -I/opt/local/include

clean: 
	/bin/rm -f ptx.cpp ptxgrammar.cpp ptxgrammar.hpp dePTX
