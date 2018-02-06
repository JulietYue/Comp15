#
# COMP 15 Project 2
# Makefile
# 
# Made By (UTLN): Qinghan Yue (qyue01)      
# On            : Apr 23 2017

CXX      = clang++
CXXFLAGS = -g -Wall -Wextra -std=c++11 -O2
LDFLAGS  = -g

gerp: main.o DirNode.o FSTree.o Simulation.o Hash.o stringProcessing.o
	${CXX} ${CXXFLAGS} -o $@ $^

main.o: main.cpp Simulation.h
Simulation.o: Simulation.h Simulation.cpp FSTree.h DirNode.h Hash.h
stringProcessing.o: stringProcessing.cpp stringProcessing.h
Hash.o: Hash.cpp Hash.h

clean:
	rm -rf gerp *.o *.dSYM

provide:
	provide comp15 proj2part3 README Makefile stringProcessing.cpp \
	stringProcessing.h Simulation.h Simulation.cpp FSTree.h DirNode.h \
	Hash.h Hash.cpp main.cpp DirNode.o FSTree.o \