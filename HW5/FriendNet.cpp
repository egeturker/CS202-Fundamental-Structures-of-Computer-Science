#include <iostream>
#include <string>
using namespace std;
#include "FriendNet.h"
#include <fstream>
#include <sstream>

/**
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 5
 */

FriendNet::FriendNet(const string fileName){

	ifstream file(fileName.c_str());
	if (file.good()){ // checks if fileName exists or not
		string s;
		getline(file,s);
		istringstream iss(s);
		iss >> listSize;

		adjList = new Person*[listSize];

		int index;
		int numFriends;
		int friendId;
		string temp;
		Person p;

		//first we create and initialize every Person except their friends
		for(int i = 0; i < listSize; i++){
			getline(file,s);
			istringstream iss(s);
			iss >> temp;
			istringstream(temp) >> index;
			adjList[index] = new Person();
			adjList[index]->id = index;
			iss >> temp;
			adjList[index]->name = temp;
			iss >> temp;
			istringstream(temp) >> numFriends;
			adjList[index]->degree = numFriends;
			adjList[index]->friends = new Person*[numFriends];
		}
		// then we traverse the file again and make friend connections (graph edges)
		ifstream file(fileName.c_str());
		getline(file,s);
		for(int i = 0; i < listSize; i++){
			getline(file,s);
			istringstream iss(s);
			iss >> temp;
			istringstream(temp) >> index;
			iss >> temp;
			iss >> temp;
			istringstream(temp) >> numFriends;
			for(int j = 0; j < numFriends; j++){
				iss >> temp;
				istringstream(temp) >> friendId;
				adjList[index]->friends[j] = adjList[friendId];
			}
		}


	}
	else
		listSize = 0;
}

FriendNet::FriendNet(const FriendNet& aNet){
	listSize = aNet.listSize;
	if ( listSize != 0){
		adjList = new Person*[listSize];
		//copy Person's first without their friends (we don't want to make connections with rhs pointers)
		for (int i = 0; i < listSize; i++){
			adjList[i] = new Person();
			adjList[i]->id = aNet.adjList[i]->id;
			adjList[i]->name = aNet.adjList[i]->name;
			adjList[i]->degree = aNet.adjList[i]->degree;
			adjList[i]->friends = new Person*[adjList[i]->degree];
		}
		//make friend connections
		for(int i = 0; i < listSize; i++){
			for(int j = 0; j < adjList[i]->degree; j++)
			adjList[i]->friends[j] = adjList[aNet.adjList[i]->friends[j]->id];
		}
	}
}

FriendNet::~FriendNet(){
	for( int i = 0; i < listSize; i++){
		delete adjList[i];
		adjList[i] = NULL;
	}
	adjList = NULL;
}

void FriendNet::listFriends(const string personName, const int hopNo){
	int index = -1;
	for(int i = 0; i < listSize; i++){
		if (adjList[i]->name == personName){
			index = i; //save the index of given person
			break;
		}
	}
	if(index == -1) //the case that person doesn't exist
		cout << personName << " does not exist in the network." << endl;
	else{
		if (hopNo <= 0) //the case that hopNo isn't positive
			cout << "People accessible from " << personName << " within " << hopNo << " hops: NOBODY";
		else {
			int friendsSoFar = 0;
			bool exists = false;
			int* tempFriends = new int[listSize]; //temp array to hold friends
			for ( int i = 0; i < hopNo; i++){ //repeat hopNo times
				if(friendsSoFar == 0){ // find 1st degree friends of given person
					for( int j = 0; j < adjList[index]->degree ; j++){
						tempFriends[j] = adjList[index]->friends[j]->id;
						friendsSoFar++;
					}
				}
				else{
					int dummy = friendsSoFar;
					for(int j = 0; j < dummy; j++){ // find friends of the people in the friendList
						for(int k = 0; k < adjList[tempFriends[j]]->degree; k++){
							for(int t = 0; t < friendsSoFar; t++){
								if(tempFriends[t] == adjList[tempFriends[j]]->friends[k]->id
										|| adjList[tempFriends[j]]->friends[k]->id == index)
								exists = true; // check if they're already in list or if they're the initial person
							}
							if( exists == false){
								tempFriends[friendsSoFar] = adjList[tempFriends[j]]->friends[k]->id;
								friendsSoFar++;
							}
							exists = false;
						}
					}
				}
			}

		cout << "People accessible from " << personName << " within " << hopNo << " hops: ";
		for ( int i = 0; i < (friendsSoFar - 1); i++)
			cout << adjList[tempFriends[i]]->name << ", ";
		if ( (friendsSoFar - 1) >= 0)
			cout << adjList[tempFriends[friendsSoFar - 1]]->name << endl;
		else
			cout << "NOBODY" << endl;


		delete tempFriends;
		tempFriends = NULL;
		}
	}
}

void FriendNet::displayAverageDegrees(){
	int comp;
	int* arr;
	double degreeCount = 0;
	int vertexCount = 0;
	arr = findComponents(comp);

	cout << "There are " << comp << " connected components. The average degrees are: "<<endl;

	for(int i = 0; i < comp; i++){
		int index = arr[i];
		int* tempQueue = new int[listSize];
		int queueRear = 0;
		bool* marked = new bool[listSize];
		for ( int j = 0; j < listSize; j++)
			marked[j] = false;
		if (marked[index] == false){
			marked[index] = true;
			degreeCount += adjList[index]->degree;
			vertexCount++;
			tempQueue[queueRear] = index;
			queueRear++;
			while(queueRear != 0){
				int x = tempQueue[0];
				for(int k = 0; k < (queueRear -1); k++)
					tempQueue[k] = tempQueue[k+1];
					queueRear--;
				for (int k = 0; k < adjList[x]->degree; k++){
					if(marked[adjList[x]->friends[k]->id] == false){
						marked[adjList[x]->friends[k]->id] = true;
						degreeCount += adjList[x]->friends[k]->degree;
						vertexCount++;
						tempQueue[queueRear] = adjList[x]->friends[k]->id;
						queueRear++;
					}
				}
			}
		}
		cout.precision(3);
		cout << "For component " << i << ": ";
		cout << degreeCount/vertexCount << endl;
		degreeCount = 0;
		vertexCount = 0;

		delete tempQueue;
		delete marked;
	}
	delete arr;
}

void FriendNet::displayDiameters(){
	int comp;
	int* arr;
	double degreeCount = 0;
	int vertexCount = 0;
	arr = findComponents(comp);
	cout << "There are " << comp << " connected components. The diameters are: "<<endl;

	bool** compArray = new bool*[comp];
	for(int i = 0; i < comp; i++){
		compArray[i] = new bool[listSize];
		for(int j = 0; j < listSize; j++)
			compArray[i][j] = false;
	}




	for(int i = 0; i < comp; i++){// find which components are in the same group, marks them as true if so
		int index = arr[i];
		int* tempQueue = new int[listSize];
		int queueRear = 0;
		bool* marked = new bool[listSize];
		for ( int j = 0; j < listSize; j++)
			marked[j] = false;
		if (marked[index] == false){
			marked[index] = true;
			compArray[i][adjList[index]->id] = true;
			tempQueue[queueRear] = index;
			queueRear++;
			while(queueRear != 0){
				int x = tempQueue[0];
				for(int k = 0; k < (queueRear -1); k++)
					tempQueue[k] = tempQueue[k+1];
					queueRear--;
				for (int k = 0; k < adjList[x]->degree; k++){
					if(marked[adjList[x]->friends[k]->id] == false){
						marked[adjList[x]->friends[k]->id] = true;
						compArray[i][adjList[x]->friends[k]->id] = true;
						tempQueue[queueRear] = adjList[x]->friends[k]->id;
						queueRear++;
					}
				}
			}
		}
		delete tempQueue;
		delete marked;
	}

	for( int i = 0; i < comp; i++){
		int longest = 0;
		for( int j = 0; j < listSize; j++){
			for( int k = 0; k < listSize; k++){
				int temp = shortestDistance(j,k);
				if(temp != -1 && compArray[i][j] == true && compArray[i][k] == true && temp > longest )
					longest = temp;
			}
		}
		cout << "For component " << i << ": " << longest << endl;

	}
	for(int i = 0; i < comp; i++)
		delete compArray[i];
	delete compArray;

}

//This function computes the shortest between two graph elements
int FriendNet::shortestDistance(int source, int destination){
	int* p = new int[listSize];
	int* d = new int[listSize];
	int* tempQueue = new int[listSize];
	int queueRear = 0;
	bool* marked = new bool[listSize];

	bool found = false;

	for(int i = 0; i < listSize; i++){
		marked[i] = false;
		d[i] = 999;
		p[i] = -1;
	}

	marked[source] = true;
	d[source] = 0;
	tempQueue[queueRear] = source;
	queueRear++;

	while(queueRear != 0){
		int x = tempQueue[0];
		for(int k = 0; k < (queueRear -1); k++)
			tempQueue[k] = tempQueue[k+1];
		queueRear--;
		for (int k = 0; k < adjList[x]->degree; k++){
			if(marked[adjList[x]->friends[k]->id] == false){
			marked[adjList[x]->friends[k]->id] = true;
			d[adjList[x]->friends[k]->id] = d[x] + 1;
			p[adjList[x]->friends[k]->id] = x;
			tempQueue[queueRear] = adjList[x]->friends[k]->id;
			queueRear++;
		}
			if(adjList[x]->friends[k]->id == destination){
				found = true;
				queueRear = 0;
				break;
			}
		}
    }
	if (found == true){
		int* path = new int[listSize];
		int t = destination;
		path[0] = t;
		int iterate = 1;
		while( p[t] != -1){
			path[iterate] = p[t];
			iterate++;
			t = p[t];
		}
		int result = d[destination];
		delete p;
		delete tempQueue;
		delete marked;
		delete path;
		delete d;
		return result;
	}
	else{
		delete p;
		delete tempQueue;
		delete marked;
		delete d;
		return -1;
	}
}

//This function finds out how many connected components are in the net with breadh first treaversal
//Returns the number of components and one vertex from each connected component in an array
int* FriendNet::findComponents(int& component){
	int index = 0;
	component = 0;
	int* compArray = new int[listSize];
	for(int i = 0; i < listSize; i++)
		compArray[i] = -1;
	int* tempQueue = new int[listSize];
	int queueRear = 0;
	bool* marked = new bool[listSize];
	for ( int i = 0; i < listSize; i++)
		marked[i] = false;
	for( int index = 0; index < listSize; index++){
		if (marked[index] == false){
			marked[index] = true;
			tempQueue[queueRear] = index;
			queueRear++;
			while(queueRear != 0){
				int x = tempQueue[0];
				for(int i = 0; i < (queueRear -1); i++)
					tempQueue[i] = tempQueue[i+1];
					queueRear--;
				for (int i = 0; i < adjList[x]->degree; i++){
					if(marked[adjList[x]->friends[i]->id] == false){
						marked[adjList[x]->friends[i]->id] = true;
						tempQueue[queueRear] = adjList[x]->friends[i]->id;
						queueRear++;
					}
				}
			}
			compArray[component] = index;
			component++;
			}
	}
	delete tempQueue;
	delete marked;
	return compArray;
}



