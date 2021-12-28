#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include "DecisionTree.h"


DecisionTree::DecisionTree(){
	root = NULL;
	numOfFeatures = 0;}

double DecisionTree::calculateEntropy( const int *classCounts, const int numClasses){
	int classTotal = 0;
	double entropy = 0;

	for (int i = 0; i < numClasses; i++){
		classTotal += classCounts[i];
	}

	for (int i = 0; i < numClasses; i++){
		if ( classCounts[i] != 0){
			double temp = (double(classCounts[i]) / double(classTotal));
			entropy += (temp * log2(temp));
		}
	}

	entropy *= -1;

	return entropy;
}

double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples,
								const int numFeatures, const bool* usedSamples, const int featureId){
	int numClasses = 2; // We need to have at least 2 classes to calculate information gain
	int x = 3;

	//Loop to check if we have more than 2 classes
	bool found = true;
	while (found){
		for(int i = 0; i < numSamples; i++){
			if ( (labels[i] == x )&& (usedSamples[i] == false)){
				numClasses++;
				x++;
				found = true;
				break;
			}
			found = false;
		}
	}

	int* classCounts = new int[numClasses];

	for( int i = 0; i < numClasses; i++)
		classCounts[i] = 0;

	int j = 1;
	while (numClasses >= j){
		for (int i = 0; i < numSamples; i++){
			if( (labels[i] == j) && (usedSamples[i] == false))
				classCounts[j-1]++;
		}
		j++;
	}


	double eBefore = calculateEntropy( classCounts, numClasses);
	int *leftClassCounts = new int[numClasses];
	int *rightClassCounts = new int[numClasses];
	for( int i = 0; i < numClasses; i++)
		rightClassCounts[i] = 0;
	for( int i = 0; i < numClasses; i++)
		leftClassCounts[i] = 0;
	j = 1;
	int left = 0;
	int right = 0;
	while(numClasses >=j){
		for(int i = 0; i< numSamples; i++){
			if((labels[i] == j) && (usedSamples[i] == false) && (data[i][featureId] == false)){
				leftClassCounts[j-1]++;
				left++;
			}

			if((labels[i] == j) && (usedSamples[i] == false) && (data[i][featureId] == true)){
				rightClassCounts[j-1]++;
				right++;
			}

		}
		j++;
	}
	double eRight = calculateEntropy( rightClassCounts, numClasses);
	double eLeft = calculateEntropy( leftClassCounts, numClasses);


	int total = left + right;
	double pLeft = double(left)/double(total);
	double pRight = double(right)/double(total);

	double eSplit = ((eRight * pRight) + (eLeft * pLeft));

	double gain = eBefore - eSplit;

	delete classCounts;
	delete leftClassCounts;
	delete rightClassCounts;

	return gain;
}




void DecisionTree::train(const bool** data, const int* labels, const int numSamples , const int numFeatures){
	if (root == NULL){
		numOfFeatures = numFeatures;
		root = new DecisionTreeNode();
		bool* usedSamples = new bool[numSamples];
		for (int i = 0 ; i < numSamples; i++)
			usedSamples[i] = false;
		double gainHigh;
		int chosenFeature;
		double gainTemp;
		gainHigh = calculateInformationGain( data, labels, numSamples, numFeatures, usedSamples, 0);
		chosenFeature = 0;
		for (int i = 1; i < numFeatures; i++){
			gainTemp = calculateInformationGain( data, labels, numSamples, numFeatures, usedSamples, i);
			if (gainTemp > gainHigh){
				gainHigh = gainTemp;
				chosenFeature = i;
			}
		}
	root->featureId = chosenFeature;
	bool* usedSamplesRight = new bool[numSamples];
	bool* usedSamplesLeft = new bool[numSamples];

	for ( int i = 0; i < numSamples; i++){
		if (data[i][chosenFeature] == true){
			usedSamplesRight[i] = false;
			usedSamplesLeft[i] = true;
		}
		else{
			usedSamplesRight[i] = true;
			usedSamplesLeft[i] = false;
		}
	}
	DecisionTreeNode* rightChild = new DecisionTreeNode( -1, -1, NULL, NULL);
	root->rightChildPtr = rightChild;
	DecisionTreeNode* leftChild = new DecisionTreeNode( -1, -1, NULL, NULL);
	root->leftChildPtr = leftChild;
	int r = isPure(labels, numSamples,usedSamplesRight);
	int l = isPure(labels, numSamples,usedSamplesLeft);
	if( r == -1 )
		DecisionTree::trainNode(data, labels, numSamples, numFeatures, usedSamplesRight, rightChild);
	else
		rightChild->decision = r;
	if( l == -1)
		DecisionTree::trainNode(data, labels, numSamples, numFeatures, usedSamplesLeft, leftChild);
	else
		leftChild->decision = l;
		delete usedSamplesRight;
		delete usedSamplesLeft;
		delete usedSamples;
		}
	}

int DecisionTree::isPure( const int* labels, const int numSamples, const bool* usedSamples){
	int temp = -1;
	for( int i = 0; i < numSamples; i++){
		if(usedSamples[i] == false){
			temp = labels[i];
			break;
		}
	}
	for( int i = 0; i < numSamples; i++){
		if( (usedSamples[i] == false) && (temp != labels[i]))
			return -1;
	}
	return temp;
}
void DecisionTree::trainNode(const bool** data, const int* labels, const int numSamples , const int numFeatures,
							 const bool* usedSamples, DecisionTreeNode* node){
	double gainHigh;
	int chosenFeature;
	double gainTemp;
	gainHigh = calculateInformationGain( data, labels, numSamples, numFeatures, usedSamples, 0);
	chosenFeature = 0;
	for (int i = 1; i < numFeatures; i++){
		gainTemp = calculateInformationGain( data, labels, numSamples, numFeatures, usedSamples, i);
		if (gainTemp > gainHigh){
			gainHigh = gainTemp;
			chosenFeature = i;
		}
	}
	node->featureId = chosenFeature;
	bool* usedSamplesRight = new bool[numSamples];
	bool* usedSamplesLeft = new bool[numSamples];
	for(int i = 0; i < numSamples; i++){
		if(usedSamples[i] == true){
			usedSamplesRight[i] = true;
			usedSamplesLeft[i] = true;
		}
		else if (data[i][chosenFeature] == true){
			usedSamplesRight[i] = false;
			usedSamplesLeft[i] = true;
		}
		else{
			usedSamplesRight[i] = true;
			usedSamplesLeft[i] = false;
		}
	}
	DecisionTreeNode* rightChild = new DecisionTreeNode( true, -1, NULL, NULL);
	node->rightChildPtr = rightChild;
	DecisionTreeNode* leftChild = new DecisionTreeNode( false, -1, NULL, NULL);
	node->leftChildPtr = leftChild;
	int r = isPure(labels, numSamples,usedSamplesRight);
	int l = isPure(labels, numSamples,usedSamplesLeft);
	if( r == -1 )
		DecisionTree::trainNode(data, labels, numSamples, numFeatures, usedSamplesRight, rightChild);
	else
		rightChild->decision = r;
	if( l == -1)
		DecisionTree::trainNode(data, labels, numSamples, numFeatures, usedSamplesLeft, leftChild);
	else
		leftChild->decision = l;
		delete usedSamplesRight;
		delete usedSamplesLeft;

}

void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures){

	bool ** data = new bool*[numSamples];
	for(int i = 0; i < numSamples; i++)
		data[i] = new bool[numFeatures];

	int* labels = new int[numSamples];

	ifstream file(fileName.c_str());
	string s;
	int k;

	for( int i = 0; i < numSamples; i++){
		getline(file, s);
		istringstream iss(s);
		for ( int j = 0; j < numFeatures; j++){
			iss >> s;
			istringstream(s) >> k;
			data[i][j] = k;
		}
		iss >> s;
		istringstream(s) >> k;
		labels [i] = k;
	}
	train ((const bool**)data, labels, numSamples, numFeatures);
}

int DecisionTree::predict(const bool* data){
	if (root == NULL)
		return -1;
	else{
		DecisionTreeNode* node = root;
		while( (*node).isLeaf() == false){
			if(data[(*node).getFeatureId()] == true)
				node = node->rightChildPtr;
			else
				node = node->leftChildPtr;
		}
	return node->decision;
	}
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples){
	bool* predictData;
	int predictResult;
	int correct = 0;
	int total = 0;
	for(int i = 0; i < numSamples; i++){
		predictData = (bool*)data[i];
		predictResult = predict(predictData);

		if( predictResult == labels[i])
			correct++;
		total++;
	}
	return (double(correct)/double(total));
}

double DecisionTree::test(const string fileName, const int numSamples){

	bool ** data = new bool*[numSamples];
	for(int i = 0; i < numSamples; i++)
		data[i] = new bool[numOfFeatures];

	int* labels = new int[numSamples];

	ifstream file(fileName.c_str());
	string s;
	int k;

	for( int i = 0; i < numSamples; i++){
		getline(file, s);
		istringstream iss(s);
		for ( int j = 0; j < numOfFeatures; j++){
			iss >> s;
			istringstream(s) >> k;
			data[i][j] = k;
		}
		iss >> s;
		istringstream(s) >> k;
		labels [i] = k;
	}
	return test((const bool**)data, labels, numSamples);

}

void DecisionTree::print(){

	DecisionTreeNode* temp = root;
	int indent = 0;
	recursivePrint( temp, indent);

}

void DecisionTree::recursivePrint( DecisionTreeNode* temp, int indent){
	if (temp != NULL){
		for(int i = 0; i < indent; i++)
			cout << " ";
		if((*temp).isLeaf())
			cout << "class=" << temp->decision <<endl;
		else
			cout << temp->featureId <<endl;
		int indentNext = indent + 1;
		recursivePrint(temp->leftChildPtr, indentNext);
		recursivePrint(temp->rightChildPtr, indentNext);
	}
}



