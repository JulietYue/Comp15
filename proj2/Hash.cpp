/*
 *
 *  COMP 15 proj2 
 *
 *  Hash.cpp
 *  Hash Table function implementation
 *  Made By (qyue01):Qinghan Yue
 *       On        :Apr 23 2017
 *
 */

#include <iostream>
#include <string>
#include <cstdlib>
#include <functional>
#include "Hash.h"


using namespace std;

//default constructor
Hash::Hash()
{
	capacity = 97007;
	size = 0;
	load_factor = 0.8;

	HashTable = new ChainNode*[capacity];

	for(int i = 0; i < capacity; i++){
		HashTable[i] = NULL;
        }
}

//default destructor
Hash::~Hash()
{
	for(int i = 0; i < capacity; i++){
		if(HashTable[i] != NULL){
			deleteNode(HashTable[i]);
		}
	}
	delete []HashTable;
	capacity = 0;
	size = 0;

}

/*
 *delete all the node starting from the given node
 *
 *parameter: ChainNode *
 *return type: void
 */
void Hash::deleteNode(ChainNode *node)
{
	if(node == NULL)
		return;

	ChainNode *temp = node;

	node = node -> next;   

        delete temp;

	while(node != NULL){
		temp = node;
		node = node -> next;
		delete temp;
	}
}

/*
 *Hash the key
 *
 *parameter: string
 *return type: void
 */
size_t Hash::HashValue(string key)
{
	hash<string> function;
	size_t slot = function(key) % capacity;
	return slot;
}

/*
 *add a new node to hash table
 *
 *parameter: string, size_t
 *return type: void
 */
void Hash::addNode(string key, size_t ind)
{
	if(size/capacity > load_factor)
		expand();

	string original = key;

	toLower(key);
	int val = HashValue(key);

	ChainNode *temp = HashTable[val];
	ChainNode *insert = helpInsert(key, original, ind);		
	insert->next = temp;
	HashTable[val] = insert;
	size ++;
}


void Hash::addNode2New(string key, size_t ind, ChainNode** Table)
{
	string original = key;

	toLower(key);
	int val = HashValue(key);

	ChainNode *temp = Table[val];
	ChainNode *insert = helpInsert(key, original, ind);		
	insert->next = temp;
	Table[val] = insert;
	size ++;
}

/*
 *help insert a new node to the hash table
 *return a pointer to the new node
 *
 *parameter: string, string, size_t
 *return type: ChainNode*
 */
ChainNode* Hash::helpInsert(string key, string original, size_t ind)
{
	ChainNode *insert = new ChainNode;
	insert->word = key;
	insert->original = original;
	insert->index = ind;
	insert->next = NULL;
	return insert;
}

/*
 *insensitive search
 *
 *parameter: string, vector<size_t>&s
 *return type: void
 */
void Hash::insensitiveSearch(string key, vector<size_t>& find)
{
	toLower(key);
	size_t index = HashValue(key);

	ChainNode *temp = HashTable[index];
	while(temp != NULL){
		if(temp->word == key){
			bool duplicate = false;
			
			for(size_t i = 0; i < find.size(); i++){
				if(temp->index == find[i]){
					duplicate = true;
					break;
				}				
			}

			if(!duplicate)
				find.push_back(temp->index);
		} 
		temp = temp->next;
	}
}

/*
 *sensitive search
 *
 *parameter: string, vector<size_t>&s
 *return type: void
 */
void Hash::sensitiveSearch(string key, vector<size_t>& find)
{
	string original = key;
	toLower(key);
	size_t index = HashValue(key);

	ChainNode *temp = HashTable[index];
	while(temp != NULL){
		if(temp->original == original){
			find.push_back(temp->index);
		} 
		temp = temp->next;
	}
}

/*
 *convert all the upper case letter to lower case
 *
 *parameter: string&
 *return type: void
 */
void Hash::toLower(string& key)
{
	for(size_t i = 0; i < key.length(); i++){
		if(key[i] >='A' && key[i] <= 'Z'){
			key[i] = int(key[i]) + 32;
		}
	}
}

/*
 *expand the table
 *
 *parameter: none
 *return type: void
 */
void Hash::expand()
{
	int oldCapacity = capacity;
	capacity = capacity * 2 + 1;
	ChainNode* *newTable = new ChainNode*[capacity];

	for(int i = 0; i < capacity; i++){
		newTable[i] = NULL;
	}

	size = 0;

	for(int i = 0; i < oldCapacity; i++){
		ChainNode* temp = HashTable[i];
		while(temp != NULL){
			addNode2New(temp->original, temp->index, newTable);
			temp = temp->next;
		}
	}

	for(int i = 0; i < oldCapacity; i++){
		if(HashTable[i] != NULL){
			deleteNode(HashTable[i]);
		}
	}
	delete[]HashTable;
	HashTable = newTable;
}














