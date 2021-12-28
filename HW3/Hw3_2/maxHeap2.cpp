#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include "maxHeap2.h"

 /* Title: Heaps and Priority Queues
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 3
 */

maxHeap2::maxHeap2(){
}

void maxHeap2::buildQueue( string fileName){
	//First, parse the txt file and put it into the array
	arraySize = 10;
	heapArray = new int*[arraySize];// we start with an array of 10
	ifstream file(fileName.c_str());
	string s;
	int k;

	getline(file, s);
	istringstream iss(s);
	iss >> numPatients;

	for(int i = 0; i < numPatients; i++){
		getline(file, s);
		istringstream iss(s);
		if( i < arraySize ){ // check if the insertion exceeds the current array size
			heapArray[i] = new int[4];
			for (int j = 0; j < 4; j++){
			iss >> s;
			istringstream(s) >> k;
			heapArray[i][j] = k;
			}
		}
		else{ // if it exceeds double the array size
			int** tempArray = new int*[arraySize*2];
			for(int t = 0; t < arraySize; t++){
				tempArray[t] = heapArray[t]; // copy the contents of old array
			}
			delete heapArray;
			heapArray = tempArray;
			arraySize = arraySize*2;

			// then add normally
			heapArray[i] = new int[4];
			for (int j = 0; j < 4; j++){
			iss >> s;
			istringstream(s) >> k;
			heapArray[i][j] = k;
			}
		}
	}

	//Turn the array into a heap
	int index = ((numPatients/2) - 1); //Last non-leaf node
	for( int i = index; i >= 0; i--)
		buildHeap(heapArray, numPatients, i);
		//printHeap(heapArray, numPatients);

}

void maxHeap2::buildHeap(int** heapArray, int numPatients, int i){

	int priorSoFar = i;
	int left = ((2*i)+1);
	int right = ((2*i)+2);

	if( (left < numPatients) && hasPriority(heapArray, left, priorSoFar))
		priorSoFar = left;
	if( (right < numPatients) && hasPriority(heapArray, right, priorSoFar))
		priorSoFar = right;
	if(priorSoFar != i){
		int* temp = heapArray[i];
		heapArray[i] = heapArray[priorSoFar];
		heapArray[priorSoFar] = temp;
		buildHeap (heapArray, numPatients, priorSoFar);

	}
}



//checks if index x has higher priority to index y or not
bool maxHeap2::hasPriority(int** heapArray, int x, int y){
	bool priority = false;
	if( heapArray[x][1] > heapArray[y][1]) //compare priority first
		priority = true;
	else if (heapArray[x][1] == heapArray[y][1]){  // if equal priority
		if(heapArray[x][2] < heapArray[y][2]) //compare arrival times
			priority = true;
		else
			priority = false;
	}
	else if(heapArray[x][1] < heapArray[y][1])
		priority = false;

	return priority;
}

//dequeues and returns the patient with highest priority
int* maxHeap2::dequeuePatient(){
	int* patient = heapArray[0];
	heapArray[0] = heapArray[numPatients-1];
	numPatients--;
	if(numPatients < (arraySize/2)){
		int** tempArray = new int*[arraySize/2];
		for(int t = 0; t < (arraySize/2); t++){
			tempArray[t] = heapArray[t]; // copy the contents of old array
		}
		delete heapArray;
		heapArray = tempArray;
		arraySize = arraySize/2;
	}
	buildHeap(heapArray,numPatients, 0);
	//printHeap(heapArray,numPatients);
	return patient;


}

//queues patient and puts it in a position according to its priority
void maxHeap2::queuePatient( int* patient){
	numPatients++;
	if(numPatients <= arraySize){
		heapArray[numPatients-1] = patient;
	}
	else {
		int** tempArray = new int*[arraySize*2];
		for(int t = 0; t < arraySize; t++){
			tempArray[t] = heapArray[t]; // copy the contents of old array
		}
		delete heapArray;
		heapArray = tempArray;
		arraySize = arraySize*2;
		heapArray[numPatients-1] = patient;
	}

	int index = ((numPatients/2) - 1); //Last non-leaf node
	for( int i = index; i >= 0; i--)
		buildHeap(heapArray, numPatients, i);

	//printHeap(heapArray,numPatients);
}

//checks if given patient has arrived at that time or not
bool maxHeap2::hasArrived(int* patient,int time){
	return (patient[2] <= time);
}
//calculates average waiting time for given number of doctors
double maxHeap2::calculateTime( int numDoctors){
	int* doctorArray = new int[numDoctors]; //this array holds remaining examination time for doctors
	int** tempArray = new int*[numPatients]; // this will be used to put the patients who didn't arrive yet (temporarily)
	int numTemp = 0; //number of patients in tempArray
	int numPatients2 = numPatients; // needed to calculate avg. time since numPatients become 0 at the end
	int time = 0;
	int temp = 0;
	int patientWaitTime = 0;
	int totalWaitTime = 0;
	bool assignPatient = false;
	int* patient = NULL;
	for (int i = 0; i < numDoctors; i++) //initially all doctors are idle
		doctorArray[i] = 0;
	while (numPatients != 0){
		for( int i= 0; i < numDoctors; i++){
			if (doctorArray[i] != 0) //for the starting condition
				doctorArray[i]--; // 1 minute passed
		}
		for (int i = 0; i < numDoctors; i++){
			if( doctorArray[i] == 0){ //if doctor is idle
				temp = numPatients;
				for(int j = 0; j < temp; j++){ //get the highest priority patient, check if it arrived
					patient = dequeuePatient();
					if (hasArrived(patient,time)){//if arrived, we found the patient
						assignPatient = true;
						break;
						}
					else{
						//if not, keep searching
						tempArray[numTemp] = patient; //put the already checked patient in temp array
						numTemp++;
					}
				}
				for (int k = 0; k < numTemp; k++){//put the patients in temp array back to the heap
					queuePatient(tempArray[k]);
					tempArray[k] = NULL;
				}
					numTemp = 0;
				if (assignPatient){
					doctorArray[i] = patient[3]; //the time doctor will be busy
					patientWaitTime = (time - patient[2]);
					if(patientWaitTime < 0)
						patientWaitTime = 0;
					totalWaitTime += patientWaitTime;
					delete patient;
					assignPatient = false;
				}
			}
		}
		time++;
	}
	delete doctorArray;
	delete tempArray;
 	return (((double)totalWaitTime) / ((double)numPatients2));
}

// THE SAME METHOD WITH CALCULATE TIME. HOWEVER THIS ALSO PRINTS WHICH DOCTOR TAKES WHICH PATIENT
// AND FOR HOW LONG THE PATIENT WAITS FOR
double maxHeap2::simulate( int numDoctors){
	int* doctorArray = new int[numDoctors]; //this array holds remaining examination time for doctors
	int** tempArray = new int*[numPatients]; // this will be used to put the patients who didn't arrive yet (temporarily)
	int numTemp = 0; //number of patients in tempArray
	int numPatients2 = numPatients; // needed to calculate avg. time since numPatients become 0 at the end
	int time = 0;
	int temp = 0;
	int patientWaitTime = 0;
	int totalWaitTime = 0;
	bool assignPatient = false;
	int* patient = NULL;
	for (int i = 0; i < numDoctors; i++) //initially all doctors are idle
		doctorArray[i] = 0;
	while (numPatients != 0){
		for( int i= 0; i < numDoctors; i++){
			if (doctorArray[i] != 0) //for the starting condition
				doctorArray[i]--; // 1 minute passed
		}
		for (int i = 0; i < numDoctors; i++){
			if( doctorArray[i] == 0){ //if doctor is idle
				temp = numPatients;
				for(int j = 0; j < temp; j++){ //get the highest priority patient, check if it arrived
					patient = dequeuePatient();
					if (hasArrived(patient,time)){//if arrived, we found the patient
						assignPatient = true;
						break;
						}
					else{
						//if not, keep searching
						tempArray[numTemp] = patient; //put the already checked patient in temp array
						numTemp++;
					}
				}
				for (int k = 0; k < numTemp; k++){//put the patients in temp array back to the heap
					queuePatient(tempArray[k]);
					tempArray[k] = NULL;
				}
					numTemp = 0;
				if (assignPatient){
					doctorArray[i] = patient[3]; //the time doctor will be busy
					patientWaitTime = (time - patient[2]);
					cout << "Doctor " << i << " takes patient " << patient[0] << " at minute " << time << " " ;
					cout << "(wait: " << patientWaitTime << " mins)" << endl;
					if(patientWaitTime < 0)
					   patientWaitTime = 0;
					totalWaitTime += patientWaitTime;
					//delete patient;
					assignPatient = false;
				}
			}
		}
		time++;
	}
	delete doctorArray;
	delete tempArray;
 	return (((double)totalWaitTime) / ((double)numPatients2));
}


void maxHeap2::printHeap(int** arr, int n)
{
    for (int i = 0; i < n; ++i){
		cout << arr[i][0] << " ";
        cout << arr[i][1] << " ";
        cout << arr[i][2] << " ";
        cout << arr[i][3] << " ";
		cout << "\n";
    }

}



