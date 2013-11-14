#ifndef SEARCHTREETESTS_H
#define SEARCHTREETESTS_H

#include <ctime>
#include <climits>
#include <bitset>

using namespace std;

template <class searchTree_t>
float ST_TestInserts(int n)
{
	comparisonCount = 0;
	// SETUP
	searchTree_t tree;

	// TIMED TEST
	clock_t t = clock();
	for(int i = 0; i < n; i++)
	{
		tree.Insert(i);
	}
	t = clock() - t;

	
	float runTime = (float)t/CLOCKS_PER_SEC;
	return runTime;
}


template <class searchTree_t>
float ST_TestRemove(int n)
{
	// SETUP
	searchTree_t tree;
	for(int i = 0; i < n; i++)
	{
		tree.Insert(i);
	}
	comparisonCount = 0;

	// TIMED TEST
	clock_t t = clock();
	for(int i = 0; i < n; i++)
	{
		tree.Remove(i);
	}
	t = clock() - t;

	float runTime = (float)t/CLOCKS_PER_SEC;
	return runTime;
}



template <class searchTree_t>
float ST_TestPredecessor(int n)
{
	// SETUP
	searchTree_t tree;
	bitset<1<<24> bitset;

	for(int i = 0; i < n/4; i++) {	
		unsigned int value = rand()%n;
		while(bitset.test(value)) value = rand()%n;
		
		bitset.set(value,true);
		tree.Insert(value);
	}
	comparisonCount = 0;

	// TIMED TEST
	clock_t t = clock();
	unsigned int result = 0;

	for(int i = 0; i < n; i++) {
		result ^= tree.Predecessor(i);
	}

	t = clock() - t;
	cout << '$' << result << '$' << endl;
	float runTime = (float)t/CLOCKS_PER_SEC;
	return runTime;
}

template <class searchTree_t>
float ST_TestInterleaved(int n)
{
	// SETUP
	searchTree_t tree;
	bitset<1<<24> bitset;
	unsigned int result = 0;

	for(int i = 0; i < n/4; i++) {	
		unsigned int value = rand()%n;
		while(bitset.test(value)) value = rand()%n;

		bitset.set(value,true);
		tree.Insert(value);
	}
	comparisonCount = 0;

	// TIMED TEST
	unsigned int pred = tree.Predecessor(rand()%n);
	if(pred == -1) pred = tree.Min();
	tree.Remove(pred);
	clock_t t = clock();

	for(int i = 0; i < n; i++) {
		tree.Insert(pred);
		pred = tree.Predecessor(rand()%n);
		if(pred == -1) pred = tree.Min();
		tree.Remove(pred);
		result ^= pred;
	}

	t = clock() - t;

	cout << '$' << result << '$' << endl;
	float runTime = (float)t/CLOCKS_PER_SEC;
	return runTime;
}


#endif