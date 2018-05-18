/**********
* Robin Park (rpark01)
* Comp15 Proj2
* Main
* Modified on 04-12-2017
**********/

#include <iostream>

#include "Gerp.h"

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "Usage: gerp directory" << endl;
		cerr << "            where: directory is a valid directory" << endl;
		return 1;
	}
	
	Gerp myProgram(argv[1]);

	string query;
	cout << "Query? ";
	while (cin >> query) {
		if (query == "@i" || query == "@insensitive") {
			cin >> query;
			myProgram.search(query, "insensitive");
		}
		else if (query == "@q" || query == "@quit") {
			cout << endl << "Goodbye! Thank you and have a nice day." << endl;
			return 1;
		}
		else
			myProgram.search(query, "sensitive");
		cout << "Query? ";
	}

	cout << endl << "Goodbye! Thank you and have a nice day." << endl;
	return 0;
}