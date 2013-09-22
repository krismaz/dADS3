#ifndef TESTS_H
#define TESTS_H

#include <ctime>
#include <climits>
#include <tuple>

using namespace std;


template<typename H, typename N>
tuple<float, int> TestInserts(int n)
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
	unsigned long comparisons = heap->getComparisons();
	float runTime = (float)t/CLOCKS_PER_SEC;
	tuple<float, unsigned long> result = tuple<float, unsigned long>(runTime, comparisons);

	// CLEANUP
	for(int i = n-1; i >= 0; i--) delete nodes[i];
	delete[] nodes;
	delete heap;

	// RETURN RESULT
	return result;
}

template<typename H, typename N>
tuple<float, int> TestDeleteMin(int n)
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
	unsigned long comparisons = heap->getComparisons();
	float runTime = (float)t/CLOCKS_PER_SEC;
	tuple<float, unsigned long> result = tuple<float, unsigned long>(runTime, comparisons);

	// CLEANUP
	delete[] nodes;
	delete heap;

	// RETURN RESULT
	return result;
}


template<typename H, typename N>
tuple<float, int> TestDecreaseKey(int n)
{
	// SETUP
	auto heap = new H(n);
	auto nodes = new N*[n]();
	int c = INT_MAX/10;
	for(int i = n-1; i >= 0; i--)
	{
		nodes[i] = heap->Insert(c,c);
		c--;
	}
	c = INT_MAX/10;

	// TIMED TEST
	clock_t t = clock();
	for(int j = 0; j < 5; j++)
	{
		for(int i = n-1; i >= 0; i--)
		{
			heap->DecreaseKey(nodes[i], c);
			c--;
		}
	}
	t = clock() - t;

	// FORMAT OUTPUT
	unsigned long comparisons = heap->getComparisons();
	float runTime = (float)t/CLOCKS_PER_SEC;
	tuple<float, unsigned long> result = tuple<float, unsigned long>(runTime, comparisons);

	// CLEANUP
	delete[] nodes;
	delete heap;

	// RETURN RESULT
	return result;
}
#endif