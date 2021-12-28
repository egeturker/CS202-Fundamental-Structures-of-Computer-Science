#include <iostream>
using namespace std;
#include "HashTable.h"

/**
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 4
 */

HashTable::HashTable( const int tableSize, const CollisionStrategy option ){
	tSize = tableSize;
	cOption = option;
	table = new Entry[ tSize];
	for ( int i = 0; i < tSize; i++)
		table[i].state = EMPTY;

}

HashTable::~HashTable(){
	delete table;

}

bool HashTable::insert( const int item ){
	int dummy = 0;
	if ( search(item, dummy) == true) // if the key exists, then we don't insert it again
		return false;

	int hash;

	if (cOption == LINEAR || cOption == QUADRATIC){
		hash = item % tSize;
		int i = 1;

		while( i < (tSize - 1)){ // probe until original hash location is reached again
			if(table[hash].state == EMPTY || table[hash].state == DELETED){
				table[hash].item = item;
				table[hash].state = OCCUPIED;
			return true;
			}
			else{
				hash = item % tSize;
				hash = (hash + probeFunc( i, cOption, item)) % tSize;
				i++;
			}
		}
		return false; // couldn't find a suitable location to insert, we return false
	}

	if(cOption == DOUBLE){
		hash = item % tSize;
		int i = 1;
		while (i < (tSize - 1)){ // I picked probing size^2 times to be the stopping condition
				if(table[hash].state == EMPTY || table[hash].state == DELETED){
					table[hash].item = item;
					table[hash].state = OCCUPIED;
					return true;
				}
				else{
					hash = item % tSize;
					hash = (hash + probeFunc( i, cOption, item)) % tSize;
					i++;
				}

		}
		return false; // if double probing couldn't find a suitable location, we return false
	}
	return false;
}

bool HashTable::remove( const int item ){
	int hash;

	if (cOption == LINEAR || cOption == QUADRATIC){
		hash = item % tSize;
		int i = 1;
		while ( i < (tSize - 1)){
			if (table[hash].state == EMPTY)
				return false;
			else if(table[hash].state == OCCUPIED && table[hash].item == item){
				table[hash].state = DELETED;
				return true;
			}
			else{
				hash = item % tSize;
				hash = (hash + probeFunc( i, cOption, item)) % tSize;
				i++;
			}
		}
		return false;
	}
	if (cOption == DOUBLE){
		hash = item % tSize;
		int i = 1;

		while ( i < (tSize - 1)){ // I picked probing size^2 times to be the stopping condition
				if(table[hash].state == EMPTY)
					return false;
				else if (table[hash].state == OCCUPIED && table[hash].item == item){
					table[hash].state = DELETED;
					return true;
				}
				else{
					hash = item % tSize;
					hash = (hash + probeFunc( i, cOption, item)) % tSize;
					i++;
				}
		}
		return false;
	}
	return false;
}

bool HashTable::search( const int item, int& numProbes ){
	int hash;

	if (cOption == LINEAR || cOption == QUADRATIC) {

		hash = item % tSize;
		int i = 1;
		numProbes = 1;

		while (i < (tSize - 1)){
			if (table[hash].state == EMPTY)
				return false;
			else if(table[hash].state == OCCUPIED && table[hash].item == item){
				return true;
			}
			else{
				hash = item % tSize;
				hash = (hash + probeFunc( i, cOption, item)) % tSize;
				i++;
				numProbes++;
			}
		}
		return false;
	}

	if (cOption == DOUBLE){
		hash = item % tSize;
		int i = 1;
		numProbes = 1;

		while ( i < (tSize - 1)){ // I picked probing size^2 times to be the stopping condition
				if(table[hash].state == EMPTY)
					return false;
				else if (table[hash].state == OCCUPIED && table[hash].item == item){
					return true;
				}
				else{
					hash = item % tSize;
					hash = (hash + probeFunc( i, cOption, item)) % tSize;
					i++;
					numProbes++;
				}
		}
		return false;
	}
	return false;

}

void HashTable::display(){
	for( int i = 0; i <tSize; i++){
		cout << i << " : " ;
		if( table[i].state == OCCUPIED)
			cout << table[i].item << endl;
		else
			cout << endl;
 	}

}

void HashTable::analyze( double& numSuccProbes, double& numUnsuccProbes ){
	numSuccProbes = 0;
	numUnsuccProbes = 0;
	int numProbes = 0;
	int div = 0;
	int div2 = tSize;
	if ( cOption == LINEAR || cOption == QUADRATIC){
		for ( int i = 0; i < tSize; i++){
			if(table[i].state == OCCUPIED){
				search(table[i].item, numProbes);
				div++;
				numSuccProbes += numProbes;
			}
		}
		numProbes = 1;
		for ( int i = 0; i < tSize; i++){
			int j = i;
			while (table[j].state != EMPTY){
				j = j + (probeFunc(numProbes, cOption, -1) % tSize);
				numProbes++;
			}
			numUnsuccProbes += numProbes;
			numProbes = 1;
		}
	}
	if ( cOption == DOUBLE){
		numProbes = 0;
		for ( int i = 0; i < tSize; i++){
			if(table[i].state == OCCUPIED){
				search(table[i].item, numProbes);
				div++;
				numSuccProbes += numProbes;
			}
		}
	}

	numSuccProbes = numSuccProbes / div;
	if (cOption == DOUBLE)
		numUnsuccProbes = -1;
	else
		numUnsuccProbes = numUnsuccProbes / div2;
}

int HashTable::probeFunc( int i, CollisionStrategy option, int key){
	if (option == LINEAR)
		return i;
	if (option == QUADRATIC)
		return i*i;
	if (option == DOUBLE){
		// reverses the key
		int reverse = 0;
		int r;
		while ( reverse != 0){
			r = reverse%10;
			reverse = reverse * 10 + r;
			key = key/10;
		}
		return i * key;
	}
}
