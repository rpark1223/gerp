CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11 -O2
LDFLAGS  = -g3

gerp: main.o Gerp.o HashTable.o FSTree.o DirNode.o
	${CXX} ${LDFLAGS} -o gerp main.o Gerp.o HashTable.o FSTree.o DirNode.o

main.o: main.cpp
Gerp.o: Gerp.h Gerp.cpp
HashTable.o: HashTable.h HashTable.cpp

clean:
	rm -rf gerp *.o *.dSYM

provide:
	provide comp15 proj2part3 main.cpp Gerp.h Gerp.cpp HashTable.h \
								HashTable.cpp Makefile README