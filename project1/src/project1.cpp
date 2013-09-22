#include <iostream>
#include "heap.h"
#include "fibheap.h"
#include "dijkstras.h"
#include "tests.h"

#define N 1000

using namespace std;

// int main(){
	
// 	DijkstraNode ** ds = new DijkstraNode*[N]();
		
// 	ds[N-1] = new DijkstraNode();
// 	for(int i = N-2; i>=0; i--)
// 	{
// 		ds[i] = new DijkstraNode();
// 		ds[i] -> Id = i;
// 		ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(1, ds[i+1]));
// 	}

// 	for(int i = N-3; i>=0; i--)
// 	{
// 	  for(int j = i+2;j<N;j++)
// 	  {
// 		int dist =  INT_MAX/10 - 2*(N-i);
// 		if(dist<0)
// 		{
// 		  cout << "BATMAN" << endl;
// 		}
// 		ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(dist, ds[j]));
// 	  }
// 	}

// 	BinDijkstra(ds, N);

// 	for(int i = 0; i<N; i++)
// 	{
// 		cout << ds[i]->Dist << " -> " << ((ds[i]->Pred == NULL) ? 0 : ds[i]->Pred->Id) << endl;
// 	}

// 	cin.get();
// 	return 0;
// }



int main(int argc, char *argv[]) {
	if(argc < 3) {
		cout << "Too few Arguments! Arguments are: test heap operations" << endl
			 << "Test: which test to run {insert, delete}" << endl
			 << "Heap: which heap to use {binary, fibonacci}" << endl
			 << "Operations: how many operation to run" << endl;
		return 0;
	}

	string test = argv[1];
	string heap = argv[2];
	int operations = atoi(argv[3]);
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
	} else {
		cout << "Invalid argument: " << test << ". Must be 'insert', 'deletemin' or 'decreasekey'" << endl;
	}
	cout << operations << "   \t" << runTime << "  \t" << comparisons << endl;
	return 0;


	
	// cout << "Hello world!" << endl;
	// FibHeap<int> * h = new FibHeap<int>(10);
	// h->Insert(0,0);
	// cout << h->DeleteMin()->Val << endl;
	// h->Insert(8,3);
	// auto n = h->Insert(9,4);
	// h->DecreaseKey(n,18);
	// h->Insert(2,2);
	// h->Insert(1,1);
	// cout << h->DeleteMin()->Val << endl;
	// cout << h->DeleteMin()->Val << endl;
	// cout << h->DeleteMin()->Val << endl;
	// cout << h->DeleteMin()->Val << endl;
	// auto n2 = h->Insert(9,5);
	// auto n3 = h->Insert(32,8);
	// h->DecreaseKey(n2,0);
	// h->Insert(1,6);
	// h->Insert(5,7);
	// h->DecreaseKey(n3,17);
	// h->DecreaseKey(n3,7);
	// cout << h->DeleteMin()->Val << endl;
	// cout << h->DeleteMin()->Val << endl;
	// cout << h->DeleteMin()->Val << endl;
	// cout << h->DeleteMin()->Val << endl;
	// cin.get();
	// return 0;
}
