#ifndef DIJKSTRAS_H
#define DIJKSTRAS_H
#include <vector>
#include <climits>
#include "heap.h"
#include "fibheap.h"


struct DijkstraNode
{
	int Id;
	int Dist;
	DijkstraNode * Pred;
	vector<pair<int, DijkstraNode*>>* Neighbours;
	void* NodeData;
	bool Visited;

	DijkstraNode()
	{
		Neighbours = new vector<pair<int, DijkstraNode*>>();
		Visited = false;
		Pred = NULL;
	}
	~DijkstraNode()
	{
		delete Neighbours;   
	}
};

template<typename H, typename N>
void Dijkstra(DijkstraNode ** nodes, int count)
{
	H* heap = new H(count);
	N* n = heap->Insert(0, nodes[0]);
	nodes[0]->NodeData = n; 
	nodes[0]->Dist = 0;
	for(int i = 1; i < count; i++)
	{
		n = heap->Insert(INT_MAX, nodes[i]);
		nodes[i]->NodeData = n;
		nodes[i]->Dist = INT_MAX;
	}
	while(!heap->IsEmpty())
	{
		N* n = heap->DeleteMin();
		DijkstraNode* dn = n->Val;
		dn->Dist = n->Key;
		dn->Visited = true;
		if(n->Key == INT_MAX)
		{
			cout << "WARNING UNREACHABLE NODE!"<<endl;
			return;
		}
		for(auto it = dn->Neighbours->begin(); it != dn->Neighbours->end(); ++it)
		{
			if((*it).second->Visited)
			{
				continue;
			}
			if(heap->DecreaseKey((N*)(*it).second->NodeData, dn->Dist + (*it).first))
			{
				(*it).second->Pred = dn;
			}
		}
		delete n;
	}
}

/*
void BinDijkstra(DijkstraNode ** nodes, int count)
{
	Heap<DijkstraNode*>* heap = new Heap<DijkstraNode*>(count);
	Node<DijkstraNode*>* n = heap->Insert(0, nodes[0]);
	nodes[0]->NodeData = n; 
	nodes[0]->Dist = 0;
	for(int i = 1; i < count;i++)
	{
		n = heap->Insert(INT_MAX, nodes[i]);
		nodes[i]->NodeData = n;
		nodes[i]->Dist = INT_MAX;
	}
	while(!heap->IsEmpty())
	{
		Node<DijkstraNode*>* n = heap->DeleteMin();
		DijkstraNode* dn = n->Val;
		dn->Dist = n->Key;
		cout << dn->Dist << endl;
		dn->Visited = true;
		if(n->Key == INT_MAX)
		{
			cout << "WARNING UNREACHABLE NODE!"<<endl;
			return;
		}
		for(auto it = dn->Neighbours->begin(); it != dn->Neighbours->end(); ++it)
		{
			if((*it).second->Visited)
			{
				continue;
			}
			if(heap->DecreaseKey((Node<DijkstraNode*>*)(*it).second->NodeData, dn->Dist + (*it).first))
			{
				(*it).second->Pred = dn;
			}
		}
		delete n;
	}
}

void FibDijkstra(DijkstraNode ** nodes, int count)
{
	FibHeap<DijkstraNode*>* heap = new FibHeap<DijkstraNode*>();
	FibNode<DijkstraNode*>* n = heap->Insert(0, nodes[0]);
	nodes[0]->NodeData = n; 
	nodes[0]->Dist = 0;
	for(int i = 1; i < count;i++)
	{
		n = heap->Insert(INT_MAX, nodes[i]);
		nodes[i]->NodeData = n;
		nodes[i]->Dist = INT_MAX;
	}
	while(!heap->IsEmpty())
	{
		FibNode<DijkstraNode*>* n = heap->DeleteMin();
		DijkstraNode* dn = n->Val;
		dn->Dist = n->Key;
		dn->Visited = true;
		if(n->Key == INT_MAX)
		{
			cout << "WARNING UNREACHABLE NODE!"<<endl;
			return;
		}
		for(auto it = dn->Neighbours->begin(); it != dn->Neighbours->end(); ++it)
		{
			if((*it).second->Visited)
			{
				continue;
			}
			if(heap->DecreaseKey((FibNode<DijkstraNode*>*)(*it).second->NodeData, dn->Dist + (*it).first))
			{
				(*it).second->Pred = dn;
			}
		}
		delete n;
	}
}
*/
#endif
