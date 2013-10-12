#ifndef VEBHEAP_H
#define VEBHEAP_H

#include "veb.h"

template<class T>
struct vEBNode
{
  unsigned int Key;
  T Val;
  vEBNode<T>(unsigned int k, T v): Key(k), Val(v) {}
};

template <class T, int bits>
class vEBHeap
{
private:
  vEBTree<bits> tree;
  T * data;
public:
  vEBNode<T> Min();
  vEBNode<T> Max();
  bool Member(unsigned int x);
  vEBNode<T> Predecessor(unsigned int x);
  void Insert(unsigned int x, T val);
  void Delete(unsigned int x);
  vEBNode<T> DeleteMin();
  vEBHeap();
  ~vEBHeap();
};

template <class T, int bits>
vEBHeap<T,bits>::vEBHeap()
{
  data = new T[1<<bits];
}

template <class T, int bits>
vEBHeap<T,bits>::~vEBHeap()
{
  delete[] data;
}


template <class T, int bits>
vEBNode<T> vEBHeap<T,bits>::Min()
{
  auto index = tree.Min();
  if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}

template <class T, int bits>
vEBNode<T> vEBHeap<T,bits>::Max()
{
  auto index = tree.Max();
  if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}

template <class T, int bits>
bool vEBHeap<T,bits>::Member(unsigned int x)
{
  return tree.Member(x);
}

template <class T, int bits>
vEBNode<T> vEBHeap<T,bits>::Predecessor(unsigned int x)
{
  auto index = tree.Predecessor(x);
  if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}

template <class T, int bits>
void  vEBHeap<T,bits>::Insert(unsigned int x, T val)
{
  data[x] = val;
  tree.Insert(x);
}

template <class T, int bits>
void  vEBHeap<T,bits>::Delete(unsigned int x)
{
  tree.Delete(x);
}

template <class T, int bits>
vEBNode<T> vEBHeap<T,bits>::DeleteMin()
{
  auto index = tree.DeleteMin();
 if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}
#endif