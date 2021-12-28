#ifndef MAX_HEAP_2_H
#define MAX_HEAP_2_H
#include <iostream>
using namespace std;

 /* Title: Heaps and Priority Queues
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 3
 */

class maxHeap2{
public:
	maxHeap2();
	void buildQueue( string fileName);
	double calculateTime( int numDoctors);
	double simulate( int numDoctors);
	int* dequeuePatient();
	void queuePatient( int* patient);
private:
	int** heapArray = NULL;
	int numPatients;
	int arraySize;
	void buildHeap(int** heapArray, int numPatients, int i);
	bool hasPriority(int** heapArray, int x, int y);
	void printHeap(int** arr, int n);
	bool hasArrived(int* patient,int time);

};

#endif

