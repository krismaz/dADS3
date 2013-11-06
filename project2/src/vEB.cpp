// vEB.cpp : Defines the entry point for the console application.

#define NDEBUG

#include "bitsmartveb.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <assert.h>
#include "vebheap.h"
#include "tests.h"
#include "oldtests.h"
#include "heap.h"
#include "fibheap.h"


#define BITS 24

using namespace std;

int main(int argc, char* argv[])
{
	assert(sizeof(unsigned int)==4);

	if(argc < 3) {
		cout << "Too few Arguments! Arguments are: test tree operations" << endl
			 << "Test: which test to run {insert, delete, interleaved}" << endl
			 << "Tree: which tree to use {VEB, bitsmart}" << endl
			 << "Operations: how many operation to run" << endl;
		return 0;
	}

	string test = argv[1];
	string tree = argv[2];
	int operations = atoi(argv[3]);
	float runTime = 0.0;

	if(operations > 1 << BITS) {
		cout << "The amount of operations is too damn high! Limit is " << (1 << BITS) << endl;
	}

	if(test == "insert") {
		if(tree == "VEB") {  
			runTime = TestInserts<int, BITS, vEBTree<BITS>>(operations);
		} else if(tree == "bitsmart") {
			runTime = TestInserts<int, BITS, BitSmartvEBTree<BITS>>(operations);
		} else if(tree == "binary") {
			tie(runTime, comparisonCount) = oldTestInserts<Heap<int>, Node<int>>(operations);
		} else if(tree == "fibonacci") {
			tie(runTime, comparisonCount) = oldTestInserts<FibHeap<int>, FibNode<int>>(operations);
		} else {
			cout << "Invalid argument: " << tree << ". Must be 'VEB', 'bitsmart', 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "deletemin") {
		if(tree == "VEB") {
			runTime = TestDeleteMin<int, BITS, vEBTree<BITS>>(operations);
		} else if(tree == "bitsmart") {
			runTime = TestDeleteMin<int, BITS, BitSmartvEBTree<BITS>>(operations);
		} else if(tree == "binary") {
			tie(runTime, comparisonCount) = oldTestDeleteMin<Heap<int>, Node<int>>(operations);
		} else if(tree == "fibonacci") {
			tie(runTime, comparisonCount) = oldTestDeleteMin<FibHeap<int>, FibNode<int>>(operations);
		} else {
			cout << "Invalid argument: " << tree << ". Must be 'VEB', 'bitsmart', 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "interleaved") {
		if(tree == "VEB") {
			runTime = TestInterleaved<int, BITS, vEBTree<BITS>>(operations);
		} else if(tree == "bitsmart") {
			runTime = TestInterleaved<int, BITS, BitSmartvEBTree<BITS>>(operations);
		} else if(tree == "binary") {
			tie(runTime, comparisonCount) = oldTestInterleaved<Heap<int>, Node<int>>(operations);
		} else if(tree == "fibonacci") {
			tie(runTime, comparisonCount) = oldTestInterleaved<FibHeap<int>, FibNode<int>>(operations);
		} else {
			cout << "Invalid argument: " << tree << ". Must be 'VEB', 'bitsmart', 'binary' or 'fibonacci'" << endl;
		}
	} else {
		cout << "Invalid argument: " << test << ". Must be 'insert', 'deletemin' or 'interleaved'" << endl;
	}

	cout << operations << "\t" << runTime << "\t" << comparisonCount << endl;
	
	return 0;







/*
	if(argc < 4) {
		cout << "Too few Arguments! Arguments are: test heap operations structure" << endl
			 << "Test: which test to run {insert, delete}" << endl
			 << "Heap: which heap to use {binary, fibonacci}" << endl
			 << "Operations: how many operation to run" << endl
			 << "Structure: What structure to run dijkstra on" << endl;
		return 0;
	}

	string test = argv[1];
	string heap = argv[2];
	int operations = atoi(argv[3]); //For Dijkstra this is N.
	int structure = atoi(argv[4]); //1=simple structure, 2=complex structure 
	float runTime = 0.0;
	unsigned long long comparisons = 0;

	if(test == "insert") {
		if(heap == "binary") {  
			
		} else if(heap == "fibonacci") {
			// cout << "#Testing " << operations << " Inserts with Fibonacci Heap" << endl;
			
		} else {
			cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "deletemin") {
		if(heap == "binary") {
			// cout << "#Testing " << operations << " DeleteMins with Binary Heap" << endl;
			
		} else if(heap == "fibonacci") {
			// cout << "#Testing " << operations << " DeleteMins with Fibonacci Heap" << endl;
			
		} else {
			cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "decreasekey") {
		if(heap == "binary") {
			// cout << "#Testing " << operations << " DecreaseKeys with Binary Heap" << endl;
			
		} else if(heap == "fibonacci") {
			// cout << "#Testing " << operations << " DecreaseKeys with Fibonacci Heap" << endl;
			
		} else {
			cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "dijkstra") {
		for(int i = 0; i < 5; i++)
		{
			if(heap == "binary") { 
				runTime += TestDijkstra<Heap<DijkstraNode*>, Node<DijkstraNode*>>(structure, operations);
			} else if(heap == "fibonacci") {
				runTime += TestDijkstra<FibHeap<DijkstraNode*>, FibNode<DijkstraNode*>>(structure, operations);
			} else {
				cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
			} 
		}
	} else {
		cout << "Invalid argument: " << test << ". Must be 'insert', 'deletemin', 'decreasekey' or 'dijkstra'" << endl;
	}

	cout << operations << "\t" << runTime << "\t" << comparisons << endl;
	
	return 0;

*/







	/*
	vEBTree<16> tree;
	for(int i = 0; i < 1<<15; i++)
	{
		tree.Insert(i);
	}
	while(tree.Min() != -1)
	{
		cout << tree.DeleteMin() << endl;
	}
	*/

	vEBHeap<int, 24, BitSmartvEBTree<24>> heap;

	heap.Insert(32,12);
	heap.Insert(14,10);
	heap.Insert(9,100);
	vEBNode<int> node = heap.DeleteMin();
	cout << node << endl;
	node = heap.Predecessor(30);
	cout << node << endl;

	cout << comparisonCount << endl;
	return 0;



	// BitSmartvEBTree<24> tree;
	// tree.Insert(89);
	// tree.Insert(189);
	// tree.Insert(289);
	// tree.Insert(9);
	// tree.Insert(8);

	// tree.Delete(289);
	// tree.Delete(9);
	
	// cout << tree.Member(89) << endl;
	// cout << tree.Member(189) << endl;
	// cout << tree.Member(289) << endl;
	// cout << tree.Member(9) << endl;
	// cout << tree.Member(8) << endl;

	// cout << tree.Min() << endl;
	// cout << tree.Max() << endl;

	// cout << tree.Predecessor(18) << endl;
	// cout << tree.Predecessor(180) << endl;
	// cout << tree.Predecessor(1800) << endl;
	// cout << tree.Predecessor(1) << endl;

	// system("PAUSE");

	return 0;
}

