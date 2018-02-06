/*
 *
 *  COMP 15 proj2 
 *
 *  stringProcessing.cpp
 *  
 *  Made By (qyue01):Qinghan Yue
 *         On       :Apr 23 2017
 *
 */

#include "stringProcessing.h"
#include <string>
#include <stdexcept>

using namespace std;

//check if the char is a num/letter
bool isAlphaNum(char curr);

//return the starting point of the word
int start(string input);

//get the end point of a word
int end(string input);

/*
 *processed the word
 *if its all made of nonsense, throw exception
 *
 *parameter:string
 *return type: string
 */
string stripNonAlphaNum(string input)
{

	int front = start(input);

	string processed;

	if(front == -1)
		return processed;

	int back = end(input);

	for(int i = front; i <= back; i++){
		processed += input[i];
	}

	return processed;
}

/*
 *find the starting point of a qualified word
 *
 *parameter:string
 *return type: int
 */
int start(string input)
{
	for(size_t i = 0; i < input.length(); i++){
		if(isAlphaNum(input[i]))
			return i;
	}
	return -1;
}

/*
 *find the ending point of a qualified word
 *
 *parameter:string
 *return type: int
 */
int end(string input)
{
	for(int i = input.length()-1; i >= 0; i--){
		if(isAlphaNum(input[i]))
			return i;
	}
	return -1;
}

/*
 *check if character is a letter or a number
 *
 *parameter:char
 *return type: bool
 */
bool isAlphaNum(char curr)
{
	if(curr >= 'a' && curr <= 'z')
		return true;
	else if(curr >= 'A' && curr <= 'Z')
		return true;
	else if(curr >= '0' && curr <= '9')
		return true;
	else 
		return false;
}
