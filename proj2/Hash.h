/*
 *
 *  COMP 15 proj2 
 *
 *  Hash.h
 *  Hash Table function declaration
 *  Made By (qyue01):Qinghan Yue
 *       On         :Apr 23 2017
 *
 */

#ifndef HASH_H_
#define HASH_H_
#include <vector>

using namespace std;

//Struct that represent each node in the hash table
//contains a word that has been converted to lowercase 
//the original word and the index of the info of the files it is in
//also has a pointer that points to the next node
struct ChainNode 
{
	string word;
	string original;
	size_t index;
	ChainNode *next;
};


class Hash
{
private:
	//Hash table's capacity
	int capacity;

	//Hash table's size(how many elements are in the table)
	int size;

	//max load factor of the table
	double load_factor;
	
	//a dynamic array of ChainNode*(hash table)
        ChainNode* *HashTable;

        //help insert a new node to the hash table
        ChainNode* helpInsert(string key, string original, size_t ind);

        //delete all the node starting from the given node
	void deleteNode(ChainNode *node);

	//add a new node to a dynamic array of ChainNode**
	void addNode2New(string key, size_t ind, ChainNode** Table);


public:
	//default constructor
	Hash();

	//default destructor
	~Hash();

	//Hash the key
	size_t HashValue(string key);

	//add a new node to HashTable
	void addNode(string key,size_t ind);

	//Expand hash table
	void expand();

	//insensitive search
	void insensitiveSearch(string key,vector<size_t>& find);

	//sensitive search
	void sensitiveSearch(string key,vector<size_t>& find);

	//convert all the upper case letter to lower case
	void toLower(string& key);


};
#endif
