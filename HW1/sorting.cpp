#include "sorting.h"
#include "auxArrayFunctions.h"
using namespace std;
#include <iostream>
#include <time.h>
 /* Title: Algorithm Efficiency and Sorting
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 1
 * Description : cpp file where sorting.cpp where insertionSort, quickSort
 *               and mergeSort are implemented
 */
	Sorting::Sorting(){}
	void Sorting::insertionSort(int *arr, int size, int &compCount, int &moveCount){
		compCount = 0;
		moveCount = 0;
		for (int i= 1; i < size ; i++){
			int next = arr[i];
			moveCount++;
			int j = i;
			while( (j > 0) && (arr[j-1] > next)){
				arr[j] = arr[j-1];
				moveCount++;
				j--;
			}
			compCount = compCount + i;
			arr[j] = next ;
			moveCount++;
			}
		}

	void Sorting::quickSort(int *arr, int size, int &compCount, int &moveCount){
		int first = 0;
		int last = size - 1;
		if ( first < last){
			int pivotIndex = partition(arr,first,last,compCount,moveCount); //gets pivot from partition function
			quickSort(arr, pivotIndex, compCount, moveCount); //sorts left of the pivot
			quickSort(&arr[pivotIndex + 1], (size - pivotIndex - 1),compCount, moveCount); //sorts right part of the pivot
		}
	}

	//swap and partition functions are implemented to be used in quickSort
	void Sorting::swap(int* x, int* y,int &moveCountSoFar){
		int temp = *x;
		*x = *y;
		*y = temp;
		moveCountSoFar = moveCountSoFar + 3;
	}

	int Sorting::partition(int* arr, int first, int last, int &compCount, int& moveCount){
		int pivot = arr[first]; //pivot is selected as the first element of array as specified in hw document
		moveCount++;
		int i = first; //index of the element smaller than pivot
		for (int j = (first + 1); j <= last; j++){
			if(arr[j] <= pivot){
			i++;
			swap(&arr[i], &arr[j],moveCount);
		}
		compCount++;
		}
		swap(&arr[first], &arr[i],moveCount);
		return i;
	}

	void Sorting::mergeSort(int *arr, int size, int &compCount, int &moveCount){
		int first = 0;
		int last = size - 1;
		if ( first < last){
		int mid = (first + last)/2;
		mergeSort(arr,mid + 1, compCount, moveCount);
		mergeSort (&arr[mid + 1] , (size - mid - 1), compCount, moveCount);
		merge(arr, first, mid, last,compCount, moveCount);
		}
	}

   //merge function is implemented to be used in mergeSort
	void Sorting::merge(int* arr, int first, int mid, int last, int &compCount, int &moveCount){
	int tempArray[first + last + 1];
	int first1 = first;
	int last1 = mid;
	int first2 = mid + 1;
	int last2 = last;
	int index = first1;
	for ( ;(first1 <= last1) && (first2 <= last2); ++index) {
		if (arr[first1] < arr[first2]) {
			tempArray[index] = arr[first1];
			++first1;
			moveCount++;
		}
		else {
			tempArray[index] = arr[first2];
			++first2;
			moveCount++;
		}
		compCount++;
	}
	for (; first1 <= last1; ++first1, ++index){
		tempArray[index] = arr[first1];
		moveCount++;
	}
	for (; first2 <= last2; ++first2, ++index){
		tempArray[index] = arr[first2];
		moveCount++;
	}
	for (index = first; index <= last; ++index){
		arr[index] = tempArray[index];
		moveCount++;
	}
	}

	void Sorting::performanceAnalysis(){
			int* arr1;
			int* arr2;
			int* arr3;
			int insertionData[24]; // To hold data
			int mergeData[24];
			int quickData[24];
			int insertionIndex = 0; // Data indexes
			int mergeIndex = 0;
			int quickIndex = 0;
			int compCount1,compCount2,compCount3,
			moveCount1,moveCount2,moveCount3;
			double time1, time2, time3;

			for (int N = 5000; N <= 30000; N = N + 5000){
				compCount1 = 0;
				compCount2 = 0;
				compCount3 = 0;
				moveCount1 = 0;
				moveCount2 = 0;
				moveCount3 = 0;



				// UNCOMMENT THE ONE TO BE TESTED
				//createAlreadySortedArrays(arr1, arr2, arr3,N);
				createNearlySortedArrays(arr1, arr2, arr3,N,N/500);


				clock_t t = clock();
				insertionSort(arr1, N, compCount1, moveCount1);
				t = clock() - t;
				time1 = (double(t)) / CLOCKS_PER_SEC * 1000;
				insertionData[insertionIndex++] = N;
				insertionData[insertionIndex++] = time1;
				insertionData[insertionIndex++] = compCount1;
				insertionData[insertionIndex++] = moveCount1;

				t = clock();
				quickSort(arr2, N, compCount2, moveCount2);
				t = clock() - t;
				time2 =  (double(t)) / CLOCKS_PER_SEC * 1000;
				quickData[quickIndex++] = N;
				quickData[quickIndex++] = time2;
				quickData[quickIndex++] = compCount2;
				quickData[quickIndex++] = moveCount2;

				t = clock();
				mergeSort(arr3, N, compCount3, moveCount3);
				t = clock() - t;
				time3 = (double(t)) / CLOCKS_PER_SEC * 1000;
				mergeData[mergeIndex++] = N;
				mergeData[mergeIndex++] = time3;
				mergeData[mergeIndex++] = compCount3;
				mergeData[mergeIndex++] = moveCount3;
			}

			cout << "-----------------------------------------------------" << endl;
			cout << "Part c - Time analysis of Insertion Sort" << endl;
			cout << "Array Size    Time Elapsed(ms)  compCount           moveCount" << endl;
			for ( int i = 0; i <= 23 ; i++){
				cout << insertionData[i] << "             ";
				if ( (i == 3) || (i == 7) || (i == 11) || (i == 15) || (i == 19) || (i == 23))
					cout << endl;
			}
			cout << "-----------------------------------------------------" << endl;
			cout << "Part c - Time analysis of Quick Sort" << endl;
			cout << "Array Size    Time Elapsed(ms)   compCount         moveCount"<< endl;
			for ( int i = 0; i <= 23 ; i++){
				cout << quickData[i] << "              ";
				if ( (i == 3) || (i == 7) || (i == 11) || (i == 15) || (i == 19) || (i == 23))
					cout << endl;
			}
			cout << "-----------------------------------------------------" << endl;
			cout << "Part c - Time analysis of Merge Sort" << endl;
			cout << "Array Size    Time Elapsed(ms)   compCount       moveCount"<< endl;
			for ( int i = 0; i <= 23 ; i++){
				cout << mergeData[i] << "              ";
				if ( (i == 3) || (i == 7) || (i == 11) || (i == 15) || (i == 19) || (i == 23))
					cout << endl;
			}
			delete arr1;
			delete arr2;
			delete arr3;


	}

