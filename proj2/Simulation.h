/*
 *
 *  COMP 15 proj2 
 *
 *  Simulation.h
 *  Gerp simulation, function declaration
 *  Made By (qyue01):Qinghan Yue
 *       On         :Apr 23 2017
 */
#ifndef SIMULATION_H_
#define SIMULATION_H_
#include "Hash.h"
#include "DirNode.h"

using namespace std;


class Simulation
{
public:
	//Default constructor
	Simulation();
	//Default destructor
	~Simulation();

	//integrate the program
	void run(string input);

private:

	//struct used to store data of the files
	struct filesData
	{
		string path;
		int line;
	};

	//Hash object
	Hash Table;

	//Vectors that hold the information of each file and line
	vector<filesData> files;

	bool checkCommand(string &key);

	//hash the data from the files 
	void hashData(string rootDir);

	//help to recursively hash the data
	void procRec(DirNode* root, string path);

	//open the file and process the information
	void checkFile(string path);

	//process each line and hash word to the hash table
	void ParseLine(string line, size_t index);

	//add new filesData to files vector
	size_t add2files(string path, int lineNum);

	//search for words according to the mode
	bool search(string& key, bool sens);

	//process the command from user
	void user();

};
#endif
