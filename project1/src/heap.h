#ifndef HEAP_H
#define HEAP_H


using namespace std;

template <class T>
struct Node
{
	int Key;
	T Val;
	int id;
	Node<T>(int k, T v, int i) : Key(k), Val(v), id(i) {}
};

template <class T>
class Heap
{
	private:
		Node<T>* *array;
		int size;
		int max;
		unsigned long comparisons;
		void print(const char *);
		void swap(int, int);
		void fixUp(int);
		void fixDown(int,int);

	public:
		Heap(int);
		~Heap();
		Node<T>* Insert(int, T);
		Node<T>* DeleteMin();
		Node<T>* FindMin();
		bool IsEmpty();
		bool DecreaseKey(Node<T>*,int);
		void resetComparisons();
		unsigned long getComparisons();
};


#define more(A, B) (A->Key > B->Key)

template <class T>
void Heap<T>::print(const char * s)
{
	return;
	cout << s << endl;
	for(int i = 1;i <=size; i++)
	{
		cout << i << " - " << array[i]->id <<  "-" << array[i]->Key << endl;
	}
}

template <class T>
void Heap<T>::swap(int i, int j)
{
	int id;
	Node<T>* tmp;
	tmp = array[i];
	array[i] = array[j];
	array[j] = tmp;
	id = array[i]->id;
	array[i]->id = array[j]->id;
	array[j]->id = id;
}

template <class T>
void Heap<T>::fixUp(int k)
{
	while (k > 1 && more(array[k/2], array[k]))
	{
		comparisons++;
		swap(k, k/2);
		k = k/2;
	}
	comparisons++; //one uncounted comparison was done to reach this
}





template <class T>
void Heap<T>::fixDown(int k, int N)
{
	int j;
	while (2*k <= N)
	{
		j = 2*k;

		comparisons++;
		if (j < N && more(array[j], array[j+1])) j++;

		comparisons++;
		if (!more(array[k], array[j])) break;

		swap(k, j); 
		k = j;
	}
}


template <class T>
Heap<T>::Heap(int maxSize) : array(new Node<T>* [maxSize+1]), size(0), max(maxSize), comparisons(0)
{
	print("Init");
}

template <class T>
Heap<T>::~Heap()
{
	delete[] array;
}

template <class T>
void Heap<T>::resetComparisons()
{
	comparisons = 0;
}

template <class T>
unsigned long Heap<T>::getComparisons()
{
	return comparisons;
}


template <class T>
Node<T>* Heap<T>::Insert(int k, T v)
{
	if(k < 0)
	{
		cout << "WARNING NEGATIVE KEY" << endl;
	}
	print("Pre-Insert");
	int nid = ++size;
	Node<T>* i = new Node<T>(k, v, nid);
	array[nid] = i;
	fixUp(size);
	print("Post-Insert");
	return i;
}

template <class T>
Node<T>* Heap<T>::DeleteMin()
{
	print("Pre-DeleteMin");
	swap(1, size); 
	fixDown(1, size-1);
	print("Post-DeleteMin"); 
	return array[size--];
}

template <class T>
Node<T>* Heap<T>::FindMin()
{
	return array[1];
}

template <class T>
bool Heap<T>::IsEmpty()
{
	return size == 0;
}

template <class T>
bool Heap<T>::DecreaseKey(Node<T>* n, int k)
{
	if(k < 0)
	{
		cout << "WARNING NEGATIVE KEY" << endl;
	}
	print("Pre-Decrease");
	if(array[n->id]->Key <= k)
	{
		print("Post-Decrease-f");
		return false;
	}
	array[n->id]->Key = k;
	fixUp(n->id);
	print("Post-Decrease");
	return true;
}

#endif
