#ifndef DECISION_TREE_NODE_H
#define DECISION_TREE_NODE_H

class DecisionTreeNode{
private:
	DecisionTreeNode(){}
	DecisionTreeNode( int d, int id,
					 DecisionTreeNode* left = NULL,
					 DecisionTreeNode* right = NULL)
					 :decision(d),featureId(id),leftChildPtr(left),rightChildPtr(right){}
	int decision;
	int featureId;
	DecisionTreeNode *leftChildPtr;
	DecisionTreeNode *rightChildPtr;

	friend class DecisionTree;
	bool isLeaf();
	int getFeatureId();
	bool getDecision();
};
#endif
