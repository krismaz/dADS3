#ifndef TESTS_H
#define TESTS_H

#include <ctime>

using namespace std;


template<typename H, typename N>
clock_t TestInserts(int n)
{
	auto heap = new H(n);
	auto nodes = new N*[n]();
	clock_t t = clock();
	for(int i = 0; i < n; i++)
	{
		nodes[i] = heap->Insert(i,i);
	}
	t = clock() - t;
	delete[] nodes;
	delete heap;
	return t;
}

template<typename H, typename N>
clock_t TestDeleteMin(int n)
{
	auto heap = new H(n);
	auto nodes = new N*[n]();

	for(int i = 0; i < n; i++)
	{
		nodes[i] = heap->Insert(i,i);
	}
	clock_t t = clock();
	while(!heap->IsEmpty())
	{
	heap->DeleteMin();
	}
	t = clock() - t;
	delete[] nodes;
	delete heap;
	return t;
}

#endif