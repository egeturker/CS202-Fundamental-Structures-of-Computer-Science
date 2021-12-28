#ifndef DECISION_TREE_H
#define DECISION_TREE_H
#include "DecisionTreeNode.h"

 /* Title: Decision Tree Homework
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 2
 * Description : Header file for DecisionTree.cpp
 *
 */
class DecisionTree {
public:
	DecisionTree();
	void train(const bool**, const int*, const int, const int);
	void train(const string, const int, const int);
	int predict(const bool*);
	double test(const bool**, const int*, const int);
	double test(const string, const int);
	void print();

private:
	double calculateEntropy( const int* classCounts, const int numClasses);
	double calculateInformationGain(const bool** data, const int* labels, const int numSamples,
									const int numFeatures, const bool* usedSamples, const int featureId);
	DecisionTreeNode* root;
	int numOfFeatures;
	int isPure( const int* labels, const int numSamples, const bool* usedSamples);
	void trainNode(const bool** data, const int* labels, const int numSamples , const int numFeatures,
								 const bool* usedSamples, DecisionTreeNode* node);
	void recursivePrint( DecisionTreeNode* temp, int indent);


};
#endif

