#ifndef HEAP_H
#define HEAP_H

template <class T>
struct Node
{
    int Key;
    T Val;
    int id;
};

template <class T>
class Heap
{
    private:
	    Node<T> * array;
	    int size;
	    int max;  

	public:
		Heap(int);
        ~Heap();
		Node<T> Insert(int, T);
		Node<T> DeleteMin();
        bool IsEmpty();
        bool DecreaseKey(Node<T>,int);
};



#define less(A, B) (A.Key < B.Key)
#define more(A, B) (A.Key > B.Key)
#define exch(A, B) { Node<T> t = A; A = B; B = t; B.id = A.id; A.id = t.id;} 

template <class T>
void fixUp(Node<T> a[], int k)
  {
    while (k > 1 && more(a[k/2], a[k]))
      { exch(a[k], a[k/2]); k = k/2; }
  }

template <class T>
void fixDown(Node<T> a[], int k, int N)
  { int j;
    while (2*k <= N)
      { j = 2*k;
        if (j < N && more(a[j], a[j+1])) j++;
        if (!more(a[k], a[j])) break;
        exch(a[k], a[j]); k = j;
      }
  }


template <class T>
Heap<T>::Heap(int maxSize)
{
    max = maxSize;
    size = 0;
    array = new Node<T>[maxSize+1];
}

template <class T>
Heap<T>::~Heap()
{
    delete array;
}

template <class T>
Node<T> Heap<T>::Insert(int k, T v)
{
    int nid = ++size;
    Node<T> i = {k, v, nid};
    array[nid] = i;
    fixUp(array, size);
    return i;
}

template <class T>
Node<T> Heap<T>::DeleteMin()
{
    exch(array[1], array[size]); 
    fixDown(array, 1, size-1); 
    return array[size--];
}

template <class T>
bool Heap<T>::IsEmpty()
{
    return size == 0;
}

template <class T>
bool Heap<T>::DecreaseKey(Node<T> n, int k)
{
    if(array[n.id].Key <= k)
    {
        return false;
    }
    array[n.id].Key = k;
    fixUp(array, n.id);
    return true;   
}

#endif
