#include <iostream>
#include "heap.h"
#include "fibheap.h"
#include "dijkstras.h"
#include "tests.h"

#define N 2050

using namespace std;

int main(){
	
	cout << "Hello world!" << endl;
	FibHeap<int> * h = new FibHeap<int>(10);
	h->Insert(0,0);
	cout << h->DeleteMin()->Val << endl;
	h->Insert(8,3);
	auto n = h->Insert(9,4);
	h->DecreaseKey(n,18);
	h->Insert(2,2);
	h->Insert(1,1);
	cout << h->DeleteMin()->Val << endl;
	cout << h->DeleteMin()->Val << endl;
	cout << h->DeleteMin()->Val << endl;
	cout << h->DeleteMin()->Val << endl;
	auto n2 = h->Insert(9,5);
	auto n3 = h->Insert(32,8);
	h->DecreaseKey(n2,0);
	h->Insert(1,6);
	h->Insert(5,7);
	h->DecreaseKey(n3,17);
	h->DecreaseKey(n3,7);
	cout << h->DeleteMin()->Val << endl;
	cout << h->DeleteMin()->Val << endl;
	cout << h->DeleteMin()->Val << endl;
	cout << h->DeleteMin()->Val << endl;
	cin.get();
	return 0;
}
