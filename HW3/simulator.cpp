#include "maxHeap1.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

 /* Title: Heaps and Priority Queues
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 3
 */

int main(int argc, char* argv[]){

	string fileName;
	string avg;
	int targetTime;
	double timeSoFar;
	if(argc == 3){ // check if  command line arguments are valid and initialize the variables
		fileName = argv[1];
		avg = argv[2];
		istringstream iss(avg);
		iss >> targetTime;
	}
	else{
		cout << "Please rerun program with correct command line arguments ";
		return -1;
	}

	maxHeap1 h;
	h.buildQueue( fileName); //build the queue with given filename

	//here we simulate to find the minimum number of doctors for given avg waiting time
	timeSoFar = 0;
	int docMin = 1;
	timeSoFar = h.calculateTime(docMin);
	h.buildQueue( fileName);
	while( targetTime < timeSoFar){
		docMin++;
		timeSoFar = h.calculateTime(docMin);
		h.buildQueue( fileName); // we have to build the heap again each time, since calculateTime method removes
		                         // all patients while working
	}
	cout << "Minimum number of doctors required: " << docMin << endl << endl;
	cout << "Simulation with " << docMin << " doctors:" <<endl << endl;
	h.simulate(docMin);
	cout << endl;
	cout << "Average waiting time: " << timeSoFar << " minutes" << endl;

	return 0;






}



