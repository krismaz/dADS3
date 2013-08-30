#ifndef HEAP_H
#define HEAP_H

template <class T>
struct Node
{
    int Key;
    T Val;
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
		void Insert(Node<T>);
		Node<T> DeleteMin(); 
};



#define less(A, B) (A.Key < B.Key)
#define more(A, B) (A.Key > B.Key)
#define exch(A, B) { Node<T> t = A; A = B; B = t; } 

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
void Heap<T>::Insert(Node<T> i)
{
 array[++size] = i; fixUp(array, size); 
}

template <class T>
Node<T> Heap<T>::DeleteMin()
{
    exch(array[1], array[size]); 
    fixDown(array, 1, size-1); 
    return array[size--];
}

#endif
