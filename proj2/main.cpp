/*
 *
 *  COMP 15 proj2 
 *
 *  main.cpp
 *  Gerp run
 *  Made By (qyue01):Qinghan Yue
 *       On         :Apr 23 2017
 *
 */
#include <iostream>
#include <string>
#include <fstream>
#include <functional>
#include "Hash.h"
#include "Simulation.h"
#include "stringProcessing.h"
#include "FSTree.h"
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc != 2 )
	{
		cout << "Usage:  gerp directory\n"
            	 << "            where:  directory is a valid directory";
        return 1;
	}

	Simulation s;
	s.run(argv[1]);
 
	return 0;
}
