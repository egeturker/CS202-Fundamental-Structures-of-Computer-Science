#include <iostream>
using namespace std;
#include "sorting.h"
#include "auxArrayFunctions.h"


int main(){
	Sorting s;
	int arr1[16] = {9,5,8,15,16,6,3,11,18,0,14,17,2,9,11,7};
	int arr2[16] = {9,5,8,15,16,6,3,11,18,0,14,17,2,9,11,7};
	int arr3[16] = {9,5,8,15,16,6,3,11,18,0,14,17,2,9,11,7};

	int compCount1 = 0;
	int compCount2 = 0;
	int compCount3 = 0;
	int moveCount1 = 0;
	int moveCount2 = 0;
	int moveCount3 = 0;

	s.insertionSort(arr1, 16, compCount1, moveCount1);
	s.quickSort(arr2,16,compCount2, moveCount2);
	s.mergeSort(arr3,16,compCount3, moveCount3);
	//1
	cout << "INSERTION SORT" << endl;
	displayArray(arr1,16);
	cout << "Comparison count:" << compCount1 << " " << "Data move count:" << moveCount1 << endl;

    //2
	cout << "QUICK SORT" << endl;
	displayArray(arr2,16);
	cout << "Comparison count:" << compCount2 << " " << "Data move count:" << moveCount2 << endl;

    //3
	cout << "MERGE SORT" << endl;
	displayArray(arr3,16);
	cout << "Comparison count:" << compCount3 << " " << "Data move count:" << moveCount3 << endl;


}


