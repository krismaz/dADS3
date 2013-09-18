#ifndef TESTS_H
#define TESTS_H

#include <ctime>
#include <climits>

using namespace std;


template<typename H, typename N>
float TestInserts(int n)
{
	auto heap = new H(n);
	auto nodes = new N*[n]();
	clock_t t = clock();
	for(int i = n-1; i >= 0; i--)
	{
		nodes[i] = heap->Insert(i,i);
	}
	t = clock() - t;
	for(int i = n-1; i >= 0; i--) {
		delete nodes[i];
	}
	delete[] nodes;
	delete heap;
	return (float)t/CLOCKS_PER_SEC;
}

template<typename H, typename N>
float TestDeleteMin(int n)
{
	auto heap = new H(n);
	auto nodes = new N*[n]();

	for(int i = n-1; i >= 0; i--)
	{
		nodes[i] = heap->Insert(i,i);
	}
	clock_t t = clock();
	while(!heap->IsEmpty())
	{
		N* node = heap->DeleteMin();
		delete node;
	}
	t = clock() - t;
	delete[] nodes;
	delete heap;
	return (float)t/CLOCKS_PER_SEC;
}


template<typename H, typename N>
clock_t TestDecrease(int n)
{
	auto heap = new H(n);
	auto nodes = new N*[n]();

	int c = INT_MAX/100;
	for(int i = n; i >= 0; i--)
	{
		nodes[i] = heap->Insert(c,c);
		c--;
	}
	clock_t t = clock();
	for(int j = 0; j < 5; j++)
	{
		for(int i = n; i > 0; i--)
		{
			heap->DecreaseKey(nodes[i], c);
			c--;
		}
	}
	t = clock() - t;
	delete[] nodes;
	delete heap;
	return t;
}
#endif