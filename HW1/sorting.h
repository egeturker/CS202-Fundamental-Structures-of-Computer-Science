#ifndef SORTING_H
#define SORTING_H

 /* Title: Algorithm Efficiency and Sorting
 * Author: Ege Türker
 * ID: 21702993
 * Section: 1
 * Assignment: 1
 * Description : Header file for sorting.cpp insertionSort, quickSort
 *               and mergeSort are implemented
 */
class Sorting {
public:
	Sorting();
    void insertionSort(int *arr, int size, int &compCount, int &moveCount);
    void quickSort(int *arr, int size, int &compCount, int &moveCount);
    void mergeSort(int *arr, int size, int &compCount, int &moveCount);
    void printArray(int array[], int size);
    void swap(int* x, int* y,int &moveCountSoFar);
    int partition(int* arr, int first, int last, int &compCount, int& moveCount);
    void merge(int* arr, int first, int mid, int last, int &compCount, int &moveCount);
	void performanceAnalysis();

};
#endif
