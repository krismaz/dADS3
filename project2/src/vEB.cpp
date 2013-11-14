// vEB.cpp : Defines the entry point for the console application.

// #define NDEBUG

#include "bitsmartveb.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <assert.h>
#include "vebheap.h"
#include "tests.h"
#include "oldtests.h"

#include "searchtreetests.h"
#include "vebsearchtree.h"
#include "stdsetwrapper.h"

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
	/***************
	* SEARCH TREES *
	***************/
	} else if(test == "st_insert") {
		if(tree == "VEB") {  
			runTime = ST_TestInserts<VebSearchTree<vEBTree<BITS>>>(operations);
		} else if(tree == "bitsmart") {
			runTime = ST_TestInserts<VebSearchTree<BitSmartvEBTree<BITS>>>(operations);
		} else if(tree == "std") {
			runTime = ST_TestInserts<VebSearchTree<StdSetWrapper>>(operations);
		} else {
			cout << "Invalid argument: " << tree << ". Must be 'VEB', 'bitsmart' or 'std'" << endl;
		}
	} else if(test == "st_remove") {
		if(tree == "VEB") {
			runTime = ST_TestRemove<VebSearchTree<vEBTree<BITS>>>(operations);
		} else if(tree == "bitsmart") {
			runTime = ST_TestRemove<VebSearchTree<BitSmartvEBTree<BITS>>>(operations);
		} else if(tree == "std") {
			runTime = ST_TestRemove<VebSearchTree<StdSetWrapper>>(operations);
		} else {
			cout << "Invalid argument: " << tree << ". Must be 'VEB', 'bitsmart' or 'std'" << endl;
		}
	} else if(test == "st_predecessor") {
		if(tree == "VEB") {
			runTime = ST_TestPredecessor<VebSearchTree<vEBTree<BITS>>>(operations);
		} else if(tree == "bitsmart") {
			runTime = ST_TestPredecessor<VebSearchTree<BitSmartvEBTree<BITS>>>(operations);
		} else if(tree == "std") {
			runTime = ST_TestPredecessor<VebSearchTree<StdSetWrapper>>(operations);
		} else {
			cout << "Invalid argument: " << tree << ". Must be 'VEB', 'bitsmart' or 'std'" << endl;
		}
	} else if(test == "st_interleaved") {
		if(tree == "VEB") {
			runTime = ST_TestInterleaved<VebSearchTree<vEBTree<BITS>>>(operations);
		} else if(tree == "bitsmart") {
			runTime = ST_TestInterleaved<VebSearchTree<BitSmartvEBTree<BITS>>>(operations);
		} else if(tree == "std") {
			runTime = ST_TestInterleaved<VebSearchTree<StdSetWrapper>>(operations);
		} else {
			cout << "Invalid argument: " << tree << ". Must be 'VEB', 'bitsmart' or 'std'" << endl;
		}
	}else {
		cout << "Invalid argument: " << test << ". Must be 'insert', 'remove', 'predecessor' or 'interleaved" << endl;
	}

	cout << operations << "\t" << runTime << "\t" << comparisonCount << endl;
	
	return 0;

}