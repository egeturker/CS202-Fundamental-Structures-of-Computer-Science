#ifndef MAX_HEAP_1_H
#define MAX_HEAP_1_H
#include <iostream>
using namespace std;

 /* Title: Heaps and Priority Queues
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 3
 */

class maxHeap1{
public:
	maxHeap1();
	void buildQueue( string fileName);
	double calculateTime( int numDoctors);
	double simulate( int numDoctors);
	int* dequeuePatient();
	void queuePatient( int* patient);
private:
	int* heapArray[2000];
	int numPatients;
	void buildHeap(int** heapArray, int numPatients, int i);
	bool hasPriority(int** heapArray, int x, int y);
	void printHeap(int** arr, int n);
	bool hasArrived(int* patient,int time);

};

#endif
