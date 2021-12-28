#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
#include "DecisionTree.h"


int main(){
	DecisionTree t;
	t.train( "train_data.txt" ,498,21);
	double i = t.test("test_data.txt",473 );
	t.print();



}



