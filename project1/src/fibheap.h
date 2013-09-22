#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <forward_list>
#include <unordered_set>
#include <algorithm>
#include <list>

using namespace std;

template <class T>
struct FibNode
{
	int Key;
	T Val;
	int Degree;
	bool Mark;
	FibNode<T>* Parent, *Child, *Left, *Right;
	FibNode(int k, T v)
	{
		Key = k;
		Val = v;
		Degree = 0;
		Mark = false;
		Parent = Child = Left = Right = NULL;
	}
};

template <class T>
class FibHeap
{
	private:
		int size;
		unsigned long long comparisons;
		FibNode<T>* min;
		FibNode<T>* roots;
		void consolidate();
		void link(FibNode<T>*, FibNode<T>*);
		void cut(FibNode<T>*, FibNode<T>*);
		void cascade(FibNode<T>*);
		void addRoot(FibNode<T>* n);
		void removeRoot(FibNode<T>* n);

	public:
		FibHeap();
		~FibHeap();
		FibHeap(int);
		FibNode<T>* Insert(int, T);
		FibNode<T>* DeleteMin();
		FibNode<T>* FindMin();
		bool DecreaseKey(FibNode<T>*, int);
		bool IsEmpty();
		void resetComparisons();
		unsigned long long getComparisons();
};

#define exch(A, B) { auto t = A; A = B; B = t; } 


template <class T>
FibHeap<T>::FibHeap() : size(0), comparisons(0), min(NULL), roots(NULL) {}

template <class T>
FibHeap<T>::FibHeap(int i) : size(0), comparisons(0), min(NULL), roots(NULL) {}

template <class T>
FibHeap<T>::~FibHeap()
{
	//delete roots;
}

template <class T>
void FibHeap<T>::resetComparisons()
{
	comparisons = 0;
}

template <class T>
unsigned long long FibHeap<T>::getComparisons()
{
	return comparisons;
}

template <class T>
void removeChild(FibNode<T>* n, FibNode<T>* p)
{
	if(p->Child == n)
	{
		p->Child = n->Right;
	}
	if(n->Right != NULL)
	{
		n->Right->Left = n->Left; 
	}
	if(n->Left != NULL)
	{
		n->Left->Right = n->Right; 
	}
}

template <class T>
void FibHeap<T>::addRoot(FibNode<T>* n)
{
	n->Left = n->Right = n->Parent = NULL;
	n->Right = roots;
	if(n->Right != NULL)
	{
		n->Right->Left = n;
	}
	roots = n;
}

template <class T>
void FibHeap<T>::removeRoot(FibNode<T>* n)
{
	if(roots == n)
	{
		roots = n->Right;
	}
	if(n->Right != NULL)
	{
		n->Right->Left = n->Left;
	}
	if(n->Left != NULL)
	{
		n->Left->Right = n->Right; 
	}
	n->Left = n->Right = n->Parent = NULL;
}

template <class T>
FibNode<T>* FibHeap<T>::Insert(int k, T v)
{

	if(k < 0)
	{
		cout << "WARNING NEGATIVE KEY" << endl;
	}
	FibNode<T> * n = new FibNode<T>(k, v);
	addRoot(n);

	comparisons++;
	if(min == NULL || min->Key > k)
	{
		min = n;
	}
	size++;
	return n; 
}

template <class T>
FibNode<T>* FibHeap<T>::DeleteMin()
{
	FibNode<T> * n = min;
	if(n != NULL)
	{
		removeRoot(n);
		for(auto it = n->Child; it != NULL; )
		{
			auto nit = it->Right;
			//removeChild(it,n);
			addRoot(it);
			it = nit;
		}
		if(size == 1)
		{
			min = NULL;
			roots = NULL;
		}
		else
		{
			consolidate();
		}
		size--;
	}
	return n;
}

template <class T>
FibNode<T>* FibHeap<T>::FindMin()
{
	return min;
}

int maxDegree(int n)
{

	//return 32;
	int i = 0;
	while(1<<i++<=n);
	return i*2;
}

template <class T>
void FibHeap<T>::consolidate()
{
	int degree = maxDegree(size);
	FibNode<T>** A = new FibNode<T>*[degree]();
	for(auto it = roots; it != NULL; )
	{
		FibNode<T> *  nit = it->Right;
		int d = it->Degree;
		while(A[d]!=NULL)
		{
			FibNode<T> * y = A[d];
			comparisons++;
			if(it->Key > y->Key)
			{
				exch(it,y);
			}
			link(y,it);
			A[d] = NULL;
			d++;
		}
		A[d]=it;
		it = nit;
	}
	min = NULL;
	for (int i = 0; i < degree; i++)
	{
		if(A[i]!=NULL)
		{
			comparisons++;
			if(min == NULL || A[i]->Key < min->Key)
			{
				min = A[i];
			}
		}
	}
	delete[] A;
}

template <class T>
void FibHeap<T>::link(FibNode<T>* y,FibNode<T>* n)
{
	removeRoot(y);
	//Add Child
	y->Right = n->Child;
	if(y->Right!=NULL)
	{
		y->Right->Left = y;
	}
	n->Child = y;
	n->Degree++;
	y->Mark = false;
	y->Parent = n;
}

template <class T>
bool FibHeap<T>::DecreaseKey(FibNode<T>* n, int k)
{
	if(k < 0)
	{
		cout << "WARNING NEGATIVE KEY" << endl;
	}
	if(k >= n->Key)
	{
		return false;
	}
	n->Key = k;
	auto p  = n->Parent;
	comparisons++;
	if(p!=NULL && k < p->Key)
	{
		cut(n, p);
		cascade(p);
	}
	if(min->Key > k)
	{
		min = n;
	}
	return true;
}


template <class T>
void FibHeap<T>::cut(FibNode<T>* n, FibNode<T>* p)
{
	removeChild(n,p);
	p->Degree--;
	addRoot(n);
	n->Mark = false;
}

template <class T>
void FibHeap<T>::cascade(FibNode<T>* n)
{
	auto p = n->Parent;
	if(p!=NULL)
	{
		if(p->Mark)
		{
			cut(n,p);
			cascade(p);
		}
		else
		{
			p->Mark = true;
		}
	}
}

template <class T>
bool FibHeap<T>::IsEmpty()
{
	return size == 0;
}

#endif
