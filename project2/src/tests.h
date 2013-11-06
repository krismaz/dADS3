#ifndef TESTS_H
#define TESTS_H

#include <ctime>
#include <climits>
#include <tuple>

using namespace std;



template <class T, int bits, class vEBTree_t>
float TestInserts(int n)
{
	comparisonCount = 0;
	// SETUP
	vEBHeap<T, bits, vEBTree_t> heap;

	// TIMED TEST
	clock_t t = clock();
	for(int i = n-1; i >= 0; i--)
	{
		heap.Insert(i,i);
	}
	t = clock() - t;

	
	float runTime = (float)t/CLOCKS_PER_SEC;
	return runTime;
}


template <class T, int bits, class vEBTree_t>
float TestDeleteMin(int n)
{
	// SETUP
	vEBHeap<T, bits, vEBTree_t> heap;
	for(int i = n-1; i >= 0; i--)
	{
		heap.Insert(i,i);
	}
	comparisonCount = 0;

	// TIMED TEST
	clock_t t = clock();
	for(int i = n-1; i >= 0; i--)
	{
		heap.DeleteMin();
	}
	t = clock() - t;

	float runTime = (float)t/CLOCKS_PER_SEC;
	return runTime;
}



template <class T, int bits, class vEBTree_t>
float TestInterleaved(int n)
{
	// SETUP
	vEBHeap<T, bits, vEBTree_t> heap;
	for(int i = n-1; i >= (n-1)/2; i--)
	{
		heap.Insert(i,i);
	}
	comparisonCount = 0;

	// TIMED TEST
	clock_t t = clock();
	for(int i = (n-1)/2; i >= 0; i--)
	{
		heap.DeleteMin();
		heap.Insert(i,i);
	}
	t = clock() - t;

	float runTime = (float)t/CLOCKS_PER_SEC;
	return runTime;
}



#endif