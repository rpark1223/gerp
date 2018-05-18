/**********
* Robin Park (rpark01)
* Comp15 Proj2
* Gerp Implementation File
* Modified on 04-15-2017
**********/

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Gerp.h"
#include "DirNode.h"
#include "FSTree.h"
#include "HashTable.h"
using namespace std;

// purpose: constructor
// parameters: none
// returns: nothing
Gerp::Gerp()
{
	// Not needed
}

// purpose: second constructor; creates an FSTree with the given root
// parameters: string
// returns: nothing
Gerp::Gerp(string treeRoot)
{
	FSTree aTree(treeRoot);
	myTree = aTree;
	DirNode *root = myTree.getRoot();

	// populate the file tree with the directory supplied as the root
	populate(root, root->getName());
}

// purpose: destructor
// parameters: none
// returns: nothing
Gerp::~Gerp()
{
	// Not needed
}

// purpose: populates the pathlines vector and the hash table
// parameters: DirNode pointer, string
// returns: void
void Gerp::populate(DirNode *node, string path)
{
	// if there are subdirectories, add each subdirectory to the filepath and
	// recurse on it
	if (node->hasSubDir()) {
		for (int i = 0; i < node->numSubDirs(); i++) {
			DirNode *subDir = node->getSubDir(i);
			string newpath = subDir->getName();

			stringstream pathname;
			pathname << path << "/" << newpath;
			string fullpath = pathname.str();

			populate(subDir, fullpath);
		}
	}

	// if the filepath has files, process each file
	if (node->hasFiles()) {
		for (int i = 0; i < node->numFiles(); i++) {
			string aFile = node->getFile(i);

			stringstream newpath;
			newpath << path << "/" << aFile;
			string fullpath = newpath.str();

			// process each file
			tableInsertion(fullpath);		
		}
	}
}

// purpose: populates pathlines vector and hash table for each file
// parameters: string, string
// returns: void
void Gerp::tableInsertion(string fullpath)
{
	ifstream infile;
	infile.open(fullpath);
	if (!infile.is_open()) {
		cerr << "File could not be opened" << endl;
		return;
	}
	int lineNum = 1;
	string line;

	// for each nonempty line in the file, add the line number and the line to
	// the filepath and add the filepath to the paths vector
	while (getline(infile, line)) {
		if (!line.empty()) {
			stringstream newpath;
			newpath << fullpath << ":" << lineNum << ": " << line;
			string indPath = newpath.str();
			paths.push_back(indPath);
			size_t index = paths.size() - 1;

			// process each line
			lineProcess(line, index);
			lineNum++;
		}
		else
			lineNum++;
	}
	infile.close();
}

// purpose: processes an individual line of input for each file; parses each
//			word in the line and inserts it into the hash table if it has no
//			repeat within the line
// parameters: string, size_t
// returns: void
void Gerp::lineProcess(string line, size_t index)
{
	string str;
	stringstream ss(line);
	vector<string> words;

	while (!ss.eof()) {
		bool duplicate = false;
		ss >> str;
		str = stripNonAlphaNum(str);
		if (str != "") {
			// if there is no duplicate of the word in the same line, insert
			for (size_t i = 0; i < words.size(); i++) {
				if (str == words[i])
					duplicate = true;
			}
			if (!duplicate) {
				vector<size_t> indices;
				indices.push_back(index);
				string noncase = convertLowercase(str);
				myTable.insert(noncase, str, indices);
				words.push_back(str);
			}
		}
	}
}

// purpose: strips trailing/leading non-alphanumeric characters from a string
// parameters: string
// returns: string
string Gerp::stripNonAlphaNum(string process)
{
	int firstChar = 0;
	int lastChar = process.length();

	if (process == "")
		return process;

	while (!isalnum(process[firstChar])) {
		firstChar++;
		if (firstChar == lastChar)
			return "";
	}

	while (!isalnum(process[lastChar - 1]))
		lastChar--;

	return process.substr(firstChar, lastChar - firstChar);
}

// purpose: converts given string to all lowercase characters
// parameters: string
// returns: string
string Gerp::convertLowercase(string process)
{
	for (size_t i = 0; i < process.length(); i++)
		process[i] = tolower(process[i]);
	return process;
}

// purpose: finds the given string in either case-sensitive or insensitive form
// parameters: string, string
// returns: void
void Gerp::search(string find, string version)
{
	find = stripNonAlphaNum(find);
	string lower = convertLowercase(find);
	vector<WordInfo> words = myTable.getWordInfo(lower, find, version);

	if (words.size() != 0)
		print(words);
	else {
		cout << find << " Not Found.";
		if (version == "sensitive")
			cout << " Try with @insensitive or @i." << endl;
		else
			cout << endl;
	}
}

// purpose: prints corresponding output from user's query
// parameters: WordInfo vector
// returns: void
void Gerp::print(vector<WordInfo> myVec)
{
	// print out the contents of the corresponding indices of the paths vector
	// to the values in the vectors of every WordInfo struct
	for (size_t i = 0; i < myVec.size(); i++) {
		for (size_t j = 0; j < myVec[i].indices.size(); j++) {
			string path = paths[myVec[i].indices[j]];
			cout << path << endl;
		}
	}
}
