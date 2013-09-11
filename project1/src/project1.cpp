#include <iostream>
#include "heap.h"
#include "fibheap.h"
#include "dijkstras.h"

#define N 2500

using namespace std;

int main(){
	cout << "Hello world!" << endl;
    DijkstraNode ** ds = new DijkstraNode*[N]();
        
    ds[N-1] = new DijkstraNode();
    for(int i = N-2; i>=0; i--)
    {
        ds[i] = new DijkstraNode();
        ds[i] -> Id = i;
        ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(1, ds[i+1]));
    }    

    BinDijkstra(ds, N);

    for(int i = 0; i<N; i++)
    {
        cout << ds[i]->Dist << " -> " << ((ds[i]->Pred == NULL) ? 0 : ds[i]->Pred->Id) << endl;
    }
	return 0;
}
