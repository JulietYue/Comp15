/*
 *
 *  COMP 15 proj2 
 *
 *  Simulation.cpp
 *  Gerp simulation, function implementation
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
#include <cstdlib>

using namespace std;

//Default constructor
Simulation::Simulation()
{
	//Do nothing
}

//Default destructor
Simulation::~Simulation()
{
	//Do nothing
}

/*
 *integrate the program
 *
 *parameter: string
 *return type: void
 */
void Simulation::run(string rootDir)
{
	hashData(rootDir);
	user();
}

/*
 *hash the data from the files using hash function
 *
 *parameter: string
 *return type: void
 */
void Simulation::hashData(string rootDir)
{
	FSTree Tree =  FSTree(rootDir);

	if(Tree.isEmpty())
		return;

	DirNode* root = Tree.getRoot();

	string path;

	procRec(root, path);

}

/*
 *help to recursively hash the data
 *
 *parameter: DirNode*, string
 *return type: void
 */
void Simulation::procRec(DirNode* root, string path)
{
	if(root == NULL)
		return;

	path += root->getName();
	path += "/";

	if(root->hasFiles()){
		int files = root->numFiles();
		for(int i = 0; i < files; i++){
			string dir = path + root->getFile(i);
			checkFile(dir);
		}
	}

	if(root->hasSubDir()){
                int sub = root->numSubDirs();
		for(int i = 0; i < sub; i++){
			procRec(root->getSubDir(i), path);
		}
	}	

}

/*
 *open specified file and process the information
 *
 *parameter: string
 *return type: void
 */
void Simulation::checkFile(string path)
{
	ifstream input;
	input.open(path.c_str());
	if (!input.is_open()){
		cerr << "Not open\n";
		exit(1);
	}  

        int lineNum = 1;
        string temp;

	while(!input.eof()){
		getline(input, temp); 

		if(temp.length() != 0){
			size_t index = add2files(path, lineNum);
			ParseLine(temp, index);
		}

		lineNum++;
	}
	input.close();
}

/*
 *add new filesData to files vector and return the index of the new instance
 *
 *parameter: string, int
 *return type: size_t
 */
size_t Simulation::add2files(string path, int lineNum)
{
	filesData newData;
	newData.path = path;
	newData.line = lineNum;
	files.push_back(newData);
	return files.size()-1;
}

/*
 *process each line and hash word to the hash table
 *
 *parameter: string, size_t
 *return type: void
 */
void Simulation::ParseLine(string line, size_t index)
{
	istringstream iss(line);
        string word;
        vector<string>temp;

        while(iss >> word) {
                word = stripNonAlphaNum(word);
                bool check = false;

                if(word.length() == 0)
                        check = true;

                for(size_t i = 0; i < temp.size(); i++){
                        if(word == temp[i]){
                                check = true;
                                break;
                        }
                }

                if(!check){
                        Table.addNode(word, index);
                        temp.push_back(word); 
                }
        }		  	
}

/*
 *search for words according to the mode
 *
 *parameter: string& , bool
 *return type: void
 */
bool Simulation::search(string& key, bool insensitive)
{
	vector<size_t> find;
	key = stripNonAlphaNum(key); 

	if(insensitive)
		Table.insensitiveSearch(key, find);
	else
		Table.sensitiveSearch(key, find);

	if (find.size() == 0)
		return false;

	for(size_t i = 0; i < find.size(); i++){
		cout << files[find[i]].path << ":" 
		     << files[find[i]].line <<": ";
		ifstream input;
		input.open(files[find[i]].path.c_str());
		if (!input.is_open()){
			cerr << "Not open\n";
			exit(1);
		} 
		string myLine; 
		for(int j = 0; j < files[find[i]].line; j++){
			getline(input, myLine);
		}
		input.close();
		cout << myLine << endl;
	}
	return true;
}

/*
 *process the command from user
 *
 *parameter: none
 *return type: void
 */
void Simulation::user()
{
	string input;

        cout << "Query? ";
	cin >> input; 
        while(!cin.eof()){
		if(checkCommand(input)){
			cout << endl 
                             << "Goodbye! Thank you and have a nice day.\n";
			exit(1);
		}
		cout << "Query? ";
		cin >> input; 
	}
	cout << endl <<  "Goodbye! Thank you and have a nice day.\n";
}

/*
 *check the user input and search for the word, 
 *return true if asked to quit the program
 *
 *parameter: string&
 *return type: bool
 */
bool Simulation::checkCommand(string &word)
{

        if(word == "@q" || word =="@quit"){
                return true;
        }

        if(word == "@i" || word == "@insensitive"){
                cin >> word;
                if(!search(word, true)){
                        cout << word << " Not Found.\n";
   		}
        }else{
                if(!search(word, false)){
                        cout << word 
                             << " Not Found. Try with @insensitive or @i.\n";
                }
        }

        return false;    
}



