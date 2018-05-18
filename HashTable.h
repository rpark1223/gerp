/**********
* Robin Park (rpark01)
* Comp15 Proj2
* Hash Table Header File
* Modified on 04-15-2017
**********/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
using namespace std;

typedef string   KeyType;

struct WordInfo {
    KeyType sensitive;
    vector<size_t> indices;
};

typedef WordInfo      ValueType;

class HashTable
{
public:
	HashTable();
	~HashTable();

	void insert(KeyType key1, KeyType key2, vector<size_t> indices);
    vector<WordInfo> getWordInfo(KeyType key1, KeyType key2, KeyType key3);

private:

    struct ChainNode {
    KeyType    key;
    ValueType  value;
    ChainNode *next;
    };

	static const int INITIAL_TABLE_SIZE = 23;
        int currentTableSize;
        int numItemsInTable;

	ChainNode  **chainedTable;

	void  expand();
    void  deleteList(ChainNode *node);
    ChainNode *newNode(KeyType key1, KeyType key2, vector<size_t> indices);
    ChainNode *getChainNode(ChainNode *nodep, KeyType key);
    void checkCapacity();
};
#endif
