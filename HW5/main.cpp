#include "FriendNet.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;


int main(int argc, char* argv[]){
	string fileName;
	if (argc == 2){
		fileName = argv[1];
	}
	else{
		cout << "Please rerun program with .txt filename as a command line argument";
	}


	FriendNet F(fileName);
	F.listFriends("Selim", 2);
	F.listFriends("Funda", 1);
	F.listFriends("Cigdem", -1);
	cout << endl;
F.listFriends("Ibrahim", 2); F.listFriends("Ibrahim", 3); cout << endl;
F.displayAverageDegrees(); cout << endl;
F.displayDiameters(); cout << endl;
return 0;
}
