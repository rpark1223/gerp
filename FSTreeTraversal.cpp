/**********
* Robin Park (rpark01)
* Comp15 Proj2
* Implementation file for tree traversal
* Modified on 04-12-2017
**********/

#include <iostream>
#include "FSTree.h"
#include "DirNode.h"
#include <string>
#include <sstream>
using namespace std;

void print(DirNode *node, string path);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Incorrect number of command line arguments" << endl;
		return 1;
	}
	
	FSTree fileTree(argv[1]);
	DirNode *root = fileTree.getRoot();
	print(root, root->getName());
}

void print(DirNode *node, string path)
{
	if (node->hasSubDir()) {
		for (int i = 0; i < node->numSubDirs(); i++) {
			DirNode *subDir = node->getSubDir(i);
			string newpath = subDir->getName();

			stringstream pathname;
			pathname << path << "/" << newpath;
			string fullpath = pathname.str();

			print (subDir, fullpath);
		}
	}

	if (node->hasFiles()) {
		for (int i = 0; i < node->numFiles(); i++) {
			string aFile = node->getFile(i);

			stringstream newpath;
			newpath << path << "/" << aFile;
			string fullpath = newpath.str();

			cout << fullpath << endl;
		}
	}
}