/**********
* Robin Park (rpark01)
* Comp15 Proj2
* Hash Table Implementation File
* Modified on 04-15-2017
**********/
#include <iostream>
#include <vector>
#include <functional>

#include "HashTable.h"
using namespace std;

// purpose: allocates/initializes empty table of INITIAL_TABLE_SIZE
// parameters: none
// returns: none
HashTable::HashTable()
{
        currentTableSize = INITIAL_TABLE_SIZE;
        numItemsInTable  = 0;

        chainedTable = new ChainNode *[currentTableSize];

        for (int i = 0; i < currentTableSize; i++)
          chainedTable[i] = NULL;
}

// purpose: delete all nodes in list starting with given node
// parameters: ChainNode pointer
// returns: void
void HashTable::deleteList(ChainNode *node)
{
  ChainNode *temp = node;
  while (temp != NULL) {
    temp = temp->next;
    delete node;
    node = temp;
  }
}

// purpose: destructor
// parameters: none
// returns: none
HashTable::~HashTable()
{
  for (int i = 0; i < currentTableSize; i++)
    deleteList(chainedTable[i]);
  delete [] chainedTable;
}

// purpose: converts a key to a hash value
// parameters: KeyType
// returns: static size_t
static size_t hashValue(KeyType key)
{
        return hash<string>{}(key);
}

// purpose: insert a wordInfo struct into the table
// parameters: KeyType, KeyType, int
// returns: void
void HashTable::insert(KeyType key1, KeyType key2, vector<size_t> inds)
{
  checkCapacity();
  size_t slot = hashValue(key1) % currentTableSize;

  // create a new node in the given slot if no word already exists there
  if (chainedTable[slot] == NULL) {
    chainedTable[slot] = newNode(key1, key2, inds);
  }

  else {
    ChainNode *nodePtr = getChainNode(chainedTable[slot], key2);

    // if the same case-sensitive word exists, concatenate the two vectors
    if (nodePtr != NULL) {
      for (size_t i = 0; i < inds.size(); i++)
        nodePtr->value.indices.push_back(inds[i]);
    }

    // add the word to the end of the linked list
    else {
      ChainNode *temp = chainedTable[slot];
      while (temp->next != NULL)
        temp = temp->next;
      temp->next = newNode(key1, key2, inds);
    }
  }
}

// purpose: creates and returns a pointer to a newNode
// parameters: KeyType, KeyType, int
// returns: ChainNode pointer
HashTable::ChainNode *HashTable::newNode
(KeyType key1, KeyType key2, vector<size_t> inds)
{
  ChainNode *newNode = new ChainNode;

  newNode->key = key1;
  newNode->value.sensitive = key2;
  for (size_t i = 0; i < inds.size(); i++)
    newNode->value.indices.push_back(inds[i]);
  newNode->next = NULL;

  numItemsInTable++;

  return newNode;
}

// purpose: gets the node in the list containing the same case sensitive word
// parameters: ChainNode pointer, KeyType
// returns: ChainNode pointer
HashTable::ChainNode *HashTable::getChainNode(ChainNode *nodep, KeyType key)
{
  ChainNode *temp = nodep;
  while (temp != NULL) {
    if (temp->value.sensitive == key)
      return temp;
    temp = temp->next;
  }
  return NULL;
}

// purpose: checks load factor and expands table if it exceeds threshold of 0.7
// parameters: none
// returns: void
void HashTable::checkCapacity()
{
  double loadFactor = numItemsInTable / currentTableSize;
  if (loadFactor >= 0.7)
    expand();
}

// purpose: expands the HashTable
// parameters: none
// returns: void
void HashTable::expand()
{
  int oldSize = currentTableSize;
  currentTableSize *= 2;

  // create pointer to the old table, then reallocate memory for the new table
  ChainNode **oldTable = chainedTable;
  chainedTable = new ChainNode *[currentTableSize];

  for (int i = 0; i < currentTableSize; i++)
    chainedTable[i] = NULL;
  numItemsInTable = 0;

  // insert each node in the list of each nonempty slot of the old table into
  // the new table
  for (int i = 0; i < oldSize; i++) {
    if (oldTable[i] != NULL) {
      ChainNode *oldNode;
      ChainNode *node = oldTable[i];
      while (node != NULL) {
        insert(node->key, node->value.sensitive, node->value.indices);
        oldNode = node;
        node = node->next;
        delete oldNode;
      }
    }
  }
  delete [] oldTable;
}

// purpose: returns a vector of all WordInfo structs corresponding to the
//          sensitive or insensitive key/user input
// parameters: KeyType, KeyType, KeyType
// returns: vector of ValueTypes
vector<ValueType> HashTable::getWordInfo
(KeyType key1, KeyType key2, KeyType key3)
{
  vector<ValueType> words;
  size_t slot = hashValue(key1) % currentTableSize;
  if (chainedTable[slot] != NULL) {
    ChainNode *temp = chainedTable[slot];

    // if the search is insensitive, retrieve every node whose key, or
    // lowercase version, is the same as the key being searched for
    if (key3 == "insensitive") {
      while (temp != NULL) {
        if (temp->key == key1)
          words.push_back(temp->value);
        temp = temp->next;
      }
      return words;
    }

    // if the search is sensitive, retrieve the one node containing the same
    // case-sensitive word as the word being searched for
    else if (key3 == "sensitive") {
      temp = getChainNode(temp, key2);
      if (temp != NULL) {
        words.push_back(temp->value);
        return words;
      }
    }
  }
  return words;
}