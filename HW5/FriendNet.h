#ifndef FRIEND_NET_H
#define FRIEND_NET_H
#include <string>
using namespace std;
/**
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 5
 */

struct Person{
	int id;
	string name;
	int degree;
	Person** friends;
} ;

class FriendNet{
public:
	FriendNet(const string fileName);
	FriendNet(const FriendNet& aNet);
	~FriendNet();

	void listFriends(const string personName, const int hopNo);

	void displayAverageDegrees();
	void displayDiameters();



private:
	Person** adjList;
	int listSize;
	int* findComponents(int& noOfComponents);
	int shortestDistance(int source, int destination);
};



#endif
