#include "HashTable.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

/**
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 4
 */


int main(int argc, char* argv[]){

	HashTable h(15, QUADRATIC);

	string fileName;
	if (argc == 2){
		fileName = argv[1];
	}
	else{
		cout << "Please rerun program with .txt filename as a command line argument";
	}
	ifstream file(fileName.c_str());
	string s;
	string operation;
	int value;
	bool b;
	while (getline(file, s)){
		istringstream iss(s);
		iss >> operation;
		iss >> s;
		istringstream(s) >> value;

		if(operation == "I"){
			b = h.insert(value);
			if (b)
				cout << value << " inserted" << endl;
			else
				cout << value << " not inserted" << endl;
		}

		else if(operation == "R"){
			b = h.remove(value);
			if (b)
				cout << value << " removed" << endl;
			else
				cout << value << " not removed" << endl;
		}

		else if(operation == "S"){
			int probe;
			b = h.search(value, probe);
			if (b)
				cout << value << " found after " << probe << " probes"  << endl;
			else
				cout << value << " not found after " << probe << " probes" << endl;
		}
		else
			cout << "Operation wasn't formatted correctly." << endl;
	}

	h.display();
	double unSuccesful;
	double succesful;
	h.analyze(succesful, unSuccesful);
	cout << "Succesful: " << succesful <<endl;
	cout << "Unsuccesful: " << unSuccesful <<endl;


	return 0;






}


