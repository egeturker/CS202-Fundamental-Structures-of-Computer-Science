#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <iostream>
using namespace std;
/**
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 4
 */
enum CollisionStrategy { LINEAR, QUADRATIC, DOUBLE };
enum State { EMPTY, OCCUPIED, DELETED };

struct Entry{
	State state;
	int item;
};

class HashTable{
public:

	HashTable( const int tableSize, const CollisionStrategy option );
	~HashTable();
	bool insert( const int item );
	bool remove( const int item );
	bool search( const int item, int& numProbes );
	void display();
	void analyze( double& numSuccProbes, double& numUnsuccProbes );
	int probeFunc( int i, CollisionStrategy option, int key);
private:
	CollisionStrategy cOption;
	int tSize;
	Entry* table;

};



#endif
