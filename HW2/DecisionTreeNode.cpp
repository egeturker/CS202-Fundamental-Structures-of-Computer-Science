#include <iostream>
using namespace std;
#include "DecisionTreeNode.h"
bool DecisionTreeNode::isLeaf(){
	if((leftChildPtr == NULL) && (rightChildPtr == NULL))
		return true;
	return false;
}
int DecisionTreeNode::getFeatureId(){
	return featureId;
}
bool DecisionTreeNode::getDecision(){
	return decision;
}
