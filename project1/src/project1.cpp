#include <iostream>
#include "heap.h"
#include "fibheap.h"
#include "dijkstras.h"
#include "tests.h"

#define N 1000

using namespace std;

int main(){
    
    DijkstraNode ** ds = new DijkstraNode*[N]();
        
    ds[N-1] = new DijkstraNode();
    for(int i = N-2; i>=0; i--)
    {
        ds[i] = new DijkstraNode();
        ds[i] -> Id = i;
        ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(1, ds[i+1]));
    }

    for(int i = N-3; i>=0; i--)
    {
      for(int j = i+2;j<N;j++)
      {
        int dist =  INT_MAX/10 - 2*(N-i);
        if(dist<0)
        {
          cout << "BATMAN" << endl;
        }
        ds[i]->Neighbours->push_front(pair<int, DijkstraNode*>(dist, ds[j]));
      }
    }

    BinDijkstra(ds, N);

    for(int i = 0; i<N; i++)
    {
        cout << ds[i]->Dist << " -> " << ((ds[i]->Pred == NULL) ? 0 : ds[i]->Pred->Id) << endl;
    }

    cin.get();
	return 0;
}

