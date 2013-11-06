#ifndef OLDTESTS_H
#define OLDTESTS_H

#include <ctime>
#include <climits>
#include <tuple>

using namespace std;


template<typename H, typename N>
tuple<float, unsigned long long> oldTestInserts(int n)
{
	// SETUP
	auto heap = new H(n);
	auto nodes = new N*[n]();

	// TIMED TEST
	clock_t t = clock();
	for(int i = n-1; i >= 0; i--)
	{
		nodes[i] = heap->Insert(i,i);
	}
	t = clock() - t;

	// FORMAT OUTPUT
	unsigned long long comparisons = heap->getComparisons();
	float runTime = (float)t/CLOCKS_PER_SEC;
	tuple<float, unsigned long long> result = tuple<float, unsigned long long>(runTime, comparisons);

	// CLEANUP
	for(int i = n-1; i >= 0; i--) delete nodes[i];
	delete[] nodes;
	delete heap;

	// RETURN RESULT
	return result;
}

template<typename H, typename N>
tuple<float, unsigned long long> oldTestDeleteMin(int n)
{
	// SETUP
	auto heap = new H(n);
	auto nodes = new N*[n]();
	for(int i = n-1; i >= 0; i--)
	{
		nodes[i] = heap->Insert(i,i);
	}
	heap->resetComparisons();

	// TIMED TEST
	clock_t t = clock();
	while(!heap->IsEmpty())
	{
		N* node = heap->DeleteMin();
		delete node;
	}
	t = clock() - t;

	// FORMAT OUTPUT
	unsigned long long comparisons = heap->getComparisons();
	float runTime = (float)t/CLOCKS_PER_SEC;
	tuple<float, unsigned long long> result = tuple<float, unsigned long long>(runTime, comparisons);

	// CLEANUP
	delete[] nodes;
	delete heap;

	// RETURN RESULT
	return result;
}


template<typename H, typename N>
tuple<float, unsigned long long> oldTestInterleaved(int n)
{
	// SETUP
	auto heap = new H(n);
	auto nodes = new N*[n]();

	for(int i = n-1; i >= (n-1)/2; i--)	{
		nodes[i] = heap->Insert(i,i);
	}

	// TIMED TEST
	clock_t t = clock();
	for(int i = (n-1)/2; i >= 0; i--)
	{
		N* node = heap->DeleteMin();
		delete node;
		nodes[i] = heap->Insert(i,i);
	}
	t = clock() - t;

	// FORMAT OUTPUT
	unsigned long long comparisons = heap->getComparisons();
	float runTime = (float)t/CLOCKS_PER_SEC;
	tuple<float, unsigned long long> result = tuple<float, unsigned long long>(runTime, comparisons);

	// CLEANUP
	delete[] nodes;
	delete heap;

	// RETURN RESULT
	return result;
}


#endif