#ifndef TESTS_H
#define TESTS_H

#include <ctime>
#include <climits>
#include <tuple>

using namespace std;


template<typename H, typename N>
tuple<float, unsigned long long> TestInserts(int n)
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
tuple<float, unsigned long long> TestDeleteMin(int n)
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
tuple<float, unsigned long long> TestDecreaseKey(int n)
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
	unsigned long long comparisons = heap->getComparisons();
	float runTime = (float)t/CLOCKS_PER_SEC;
	tuple<float, unsigned long long> result = tuple<float, unsigned long long>(runTime, comparisons);

	// CLEANUP
	delete[] nodes;
	delete heap;

	// RETURN RESULT
	return result;
}

//Dijkstra test methods

template<typename H, typename N>
float TestDijkstra(int structure, int NodeNumber){

	DijkstraNode ** ds = new DijkstraNode*[NodeNumber]();
		
 	if(structure == 1){//Simple linear structure
	 	ds[NodeNumber-1] = new DijkstraNode();

	 	//Every node is connected to next node, with distance 100 + 2*(NodeNumber-i).
		for(int i = NodeNumber-2; i>=0; i--)
	 	{
	 		ds[i] = new DijkstraNode();
	 		ds[i] -> Id = i;
	 		int distance = i; //100 + 2*(NodeNumber-i);
	 		ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(distance, ds[i+1])); //Distance=100 + 2*(NodeNumber-i) and Neighbour is next node.
	 	}
	}

	if(structure == 2){//Complex structure
		
		//Create nodes
		for(int i = 0; i<NodeNumber; i++)
	 	{
	 		ds[i] = new DijkstraNode();
	 		ds[i] -> Id = i;	 		
	 	}

	 	//Create neighbour connections
	 	for(int i = NodeNumber-3; i>=0; i--) //i=0
	 	{
	 	  for(int j = i+2;j<NodeNumber; j++) //j=2
	 	  {
	 		int dist = j; //100 + 2*(NodeNumber-i); //distance between nodes

	 		if(dist<0) //If negative distance between nodes, failure
	 		{
	 		  cout << "Failure; Negative dist" << endl;
	 		  exit(1);
	 		}

	 		if(i == 0){
				ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(dist, ds[1]));
	 		}

	 		ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(dist, ds[j])); //node 997 has node 999 as neighbour.
	 	  }
	 	}
	}

	clock_t t = clock();
 	Dijkstra<H, N>(ds, NodeNumber);
 	t = clock() - t;
 	float runTime = (float)t/CLOCKS_PER_SEC;
 	
 	delete[] ds;

 	return runTime;


}



#endif