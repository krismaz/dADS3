#include <iostream>
#include "heap.h"
#include "fibheap.h"
#include "dijkstras.h"

using namespace std;

int main(){
	cout << "Hello world!" << endl;
    DijkstraNode ** ds = new DijkstraNode*[3]();
    for(int i = 0; i<3; i++)
    {
        ds[i] = new DijkstraNode();
    }
    ds[0]->Id = 1;
    ds[1]->Id = 2;
    ds[2]->Id = 3;
    ds[0]->Neighbours->push_front(pair<int, DijkstraNode*>(4, ds[1]));
    ds[0]->Neighbours->push_front(pair<int, DijkstraNode*>(7, ds[2]));
    ds[1]->Neighbours->push_front(pair<int, DijkstraNode*>(1, ds[2]));
    
    FibDijkstra(ds, 3);

    for(int i = 0; i<3; i++)
    {
        cout << ds[i]->Dist << " -> " << ((ds[i]->Pred == NULL) ? 0 : ds[i]->Pred->Id) << endl;
    }
	return 0;
}
