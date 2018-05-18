/**********
* Robin Park
* Gerp Header File
**********/
#ifndef GERP_H
#define GERP_H

#include "DirNode.h"
#include "FSTree.h"
#include "HashTable.h"

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Gerp {

public:

	Gerp();
	Gerp(string treeRoot);
	~Gerp();
	void populate(DirNode *node, string path);
	void tableInsertion(string fullpath);
	void lineProcess(string line, size_t index);
	string stripNonAlphaNum(string);
	string convertLowercase(string process);
	void search(string find, string version);
	void print(vector<WordInfo> myVec);

private:

	FSTree myTree;

	HashTable myTable;

	vector<string> paths;

};

#endif
