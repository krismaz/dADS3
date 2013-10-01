#include <iostream>
#include "heap.h"
#include "fibheap.h"
#include "dijkstras.h"
#include "tests.h"


using namespace std;

int main(int argc, char *argv[]) {
	
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
	float runTime = -1.0;
	unsigned long long comparisons = 0;

	if(test == "insert") {
		if(heap == "binary") {	
			// cout << "#Testing " << operations << " Inserts with Binary Heap" << endl;
			tie(runTime, comparisons) = TestInserts<Heap<int>, Node<int>>(operations);
		} else if(heap == "fibonacci") {
			// cout << "#Testing " << operations << " Inserts with Fibonacci Heap" << endl;
			tie(runTime, comparisons) = TestInserts<FibHeap<int>, FibNode<int>>(operations);
		} else {
			cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "deletemin") {
		if(heap == "binary") {
			// cout << "#Testing " << operations << " DeleteMins with Binary Heap" << endl;
			tie(runTime, comparisons) = TestDeleteMin<Heap<int>, Node<int>>(operations);
		} else if(heap == "fibonacci") {
			// cout << "#Testing " << operations << " DeleteMins with Fibonacci Heap" << endl;
			tie(runTime, comparisons) = TestDeleteMin<FibHeap<int>, FibNode<int>>(operations);
		} else {
			cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "decreasekey") {
		if(heap == "binary") {
			// cout << "#Testing " << operations << " DecreaseKeys with Binary Heap" << endl;
			tie(runTime, comparisons) = TestDecreaseKey<Heap<int>, Node<int>>(operations);
		} else if(heap == "fibonacci") {
			// cout << "#Testing " << operations << " DecreaseKeys with Fibonacci Heap" << endl;
			tie(runTime, comparisons) = TestDecreaseKey<FibHeap<int>, FibNode<int>>(operations);
		} else {
			cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
		}
	} else if(test == "dijkstra") {
		if(heap == "binary") {
			runTime = TestDijkstra<Heap<DijkstraNode*>, Node<DijkstraNode*>>(structure, operations);
		} else if(heap == "fibonacci") {
			runTime = TestDijkstra<FibHeap<DijkstraNode*>, FibNode<DijkstraNode*>>(structure, operations);
		} else {
			cout << "Invalid argument: " << heap << ". Must be 'binary' or 'fibonacci'" << endl;
		}		
	} else {
		cout << "Invalid argument: " << test << ". Must be 'insert', 'deletemin', 'decreasekey' or 'dijkstra'" << endl;
	}

	cout << operations << "\t" << runTime << "\t" << comparisons << endl;
	
	return 0;
}