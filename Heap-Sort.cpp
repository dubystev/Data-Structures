// Heap-Sort.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <conio.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>
using namespace std;

const int SIZE = 2000;

void HEAPIFY(int *A, int i, int heapsize)
{
	int largest;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if((left <= heapsize) && (A[left] > A[i])) 
		largest = left;
	else
		largest = i;

	if((right <= heapsize) && (A[right] > A[largest])) 
		largest = right;

	if(largest != i)
	{
		swap(A[i], A[largest]);
		HEAPIFY(A, largest, heapsize);
	}
}

void BUILD_HEAP(int *A, int size)
{
	int n = size - 1;
	for(int i = n/2; i >= 0; i--)
		HEAPIFY(A, i, n);
}

void HEAPSORT(int *A, int n)
{
	int i;
	BUILD_HEAP(A, n);
	for(i = n - 1; i >= 1; i--)
	{
		swap(A[0], A[i]);
		HEAPIFY(A, 0, i-1);
	}
}

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
	int *arr;
	int m = SIZE; //array input size;
	cout<<"\n\nImplementation of the Heap-Sort Algorithm";
	/*cout<<"\n\nEnter array size: ";
	cin>>m;*/

	arr = new int[m];
	/*cout<<"\n\nInput elements of the array\n";
	for(int i=0; i<m; i++)
		cin>>arr[i];*/

	//fill input array randomly
	srand(static_cast<unsigned>(time(NULL)));
	for(int i=0; i<SIZE; i++)
	{
		int randNum = 0;
		int temp;

		int num = rand();
		temp = 1 + (num % SIZE); //generate a random number between 1 and SIZE
		randNum = temp;
		arr[i] = randNum;//randNum;
	}

	cout<<"\n\nUnsorted Array\n";
	for(int i=0; i<m; i++)
		cout<<arr[i]<<"\t";


	_getch();
	time_t start = clock();
	HEAPSORT(arr, m); //Heap-Sort called on the array
	time_t stop = clock();
	time_t avg = stop - start;
	cout<<"\n\nTime taken to sort (in clock ticks): "<<avg;
	_getch();

	cout<<"\n\nArray after sorting\n";
	for(int i=0; i<m; i++)
		cout<<arr[i]<<"\t";

	_getch(); 
	return 0;
}

