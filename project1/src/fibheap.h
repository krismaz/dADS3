#ifndef FIBHEAP_H
#define FIBHEAP_H

#include <forward_list>
#include <unordered_set>
#include <algorithm>

using namespace std;

template <class T>
struct FibNode
{
    int Key;
    T Val;
    int Degree;
    bool Mark;
    FibNode<T>* Parent;
    unordered_set<FibNode<T>*>* Children;
};

template <class T>
class FibHeap
{
    private:
	    int size;
        FibNode<T>* min;
        unordered_set<FibNode<T>*>* roots;
        void consolidate();
        void link(FibNode<T>*, FibNode<T>*);
        void cut(FibNode<T>*, FibNode<T>*);
        void cascade(FibNode<T>*);

	public:
		FibHeap();
        ~FibHeap();
		FibNode<T>* Insert(int, T);
		FibNode<T>* DeleteMin();
        bool DecreaseKey(FibNode<T>*, int);
};

#define exch(A, B) { auto t = A; A = B; B = t; } 


template <class T>
FibHeap<T>::FibHeap()
{
    size = 0;
    min = NULL;
    roots = new unordered_set<FibNode<T>*>();
}

template <class T>
FibHeap<T>::~FibHeap()
{
    delete roots;
}

template <class T>
FibNode<T>* FibHeap<T>::Insert(int k, T v)
{
    FibNode<T> * n = new FibNode<T>();
    n->Key = k;
    n->Val = v;
    n->Degree = 0;
    n->Mark = false;
    n->Children = new unordered_set<FibNode<T>*>();
    roots->insert(n);
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
        for(auto it = n->Children->begin(); it != n->Children->end(); ++it)
        {
            FibNode<T>* c = *it;
            roots->insert(c);
            c->Parent = NULL;
        }
        roots->erase(n);
        if(size == 1)
        {
            min = NULL;
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
void FibHeap<T>::consolidate()
{
    //TODO:Actually find a way to do fast reverse fibonacci, or make this a list
    FibNode<T>* A[32] = {}; 
    for(int i = 0; i<32; i++)
    {
        A[i] = NULL;
    }
    forward_list<FibNode<T>*>* erase = new forward_list<FibNode<T>*>();
    for(auto it = roots->begin(); it != roots->end(); ++it)
    {
        FibNode<T> *  n = *it;
        int d = n->Degree;
        while(A[d]!=NULL)
        {
            FibNode<T> * y = A[d];
            if(n->Key > y->Key)
            {
                exch(n,y);
            }
            erase->push_front(y);
            link(y,n);
            A[d] = NULL;
            d++;
        }
        A[d]=n;
    }
    for(auto it = erase->begin(); it != erase->end(); ++it)
    {
        roots->erase(*it);
    }
    min = NULL;
    for (int i = 0; i < 32; i++)
    {
       if(A[i]!=NULL)
       {
         if(min == NULL || A[i]->Key < min->Key)
         {
            min = A[i];
         }
       }
    }
}

template <class T>
void FibHeap<T>::link(FibNode<T>* y,FibNode<T>* n)
{
    n->Children->insert(y);
    n->Degree++;
    y->Mark = false;
}

template <class T>
bool FibHeap<T>::DecreaseKey(FibNode<T>* n, int k)
{
    if(k >= n->Key)
    {
        return false;
    }
    n->Key = k;
    auto p  = n->Parent;
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
    p->Children->erase(n);
    roots->insert(n);
    n->Parent = NULL;
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

#endif
