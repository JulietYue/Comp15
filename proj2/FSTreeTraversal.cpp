/*
 *
 *  COMP 15 proj2 
 *
 *  FSTreeTraversal.cpp
 *  
 *  Modified By (UTLN):qyue01
 *           On       :Apr 13 2017
 *
 */

#include "FSTree.h"
#include "DirNode.h"
#include <iostream>
using namespace std;

//print files and directories recursively
void printRec(DirNode* root, string path);

int main(int argc, char* argv[])
{
	if(argc < 2)
		return 0;

	FSTree newTree =  FSTree(argv[1]);

	if(newTree.isEmpty())
		return 0;

        DirNode* root = newTree.getRoot();

        string path;

        printRec(root, path);

	return 0;
}

/*
 * help to print directories recursively
 *
 * parameter: DirNode* root, string 
 * return type: void
 *
 */
void printRec(DirNode* root, string path)
{
	if(root == NULL)
		return;

	path += root->getName();
	path += "/";

        //print out the files in the current directories
	if(root->hasFiles()){
		int files = root->numFiles();
		for(int i = 0; i < files; i++){
			cout << path << root->getFile(i) << endl;
		}
	}
	
	//go to sub directories if there are some
        if(root->hasSubDir()){
                int sub = root->numSubDirs();
		for(int i = 0; i < sub; i++){
			/*if(root->getSubDir(i)->isEmpty()){
				return;
			}*/
			printRec(root->getSubDir(i), path);
		}
        }	
}

















