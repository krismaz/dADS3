#ifndef VEBHEAP_H
#define VEBHEAP_H

#include "veb.h"
#include "bitsmartveb.h"
#include "sstream"

template<class T>
struct vEBNode
{
  unsigned int Key;
  T Val;
  vEBNode<T>(unsigned int k, T v): Key(k), Val(v) {}
};

ostream& operator<<(ostream& stream, vEBNode<int> node) {
  ostringstream  convert;
  convert << node.Key << ", " << node.Val;
  return stream << convert.str();
}

template <class T, int bits, class vEBTree_t>
class vEBHeap
{
private:
  vEBTree_t tree;
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

template <class T, int bits, class vEBTree_t>
vEBHeap<T,bits,vEBTree_t>::vEBHeap()
{
  data = new T[1<<bits];
}

template <class T, int bits, class vEBTree_t>
vEBHeap<T,bits,vEBTree_t>::~vEBHeap()
{
  delete[] data;
}


template <class T, int bits, class vEBTree_t>
vEBNode<T> vEBHeap<T,bits, vEBTree_t>::Min()
{
  auto index = tree.Min();
  if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}

template <class T, int bits, class vEBTree_t>
vEBNode<T> vEBHeap<T,bits, vEBTree_t>::Max()
{
  auto index = tree.Max();
  if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}

template <class T, int bits, class vEBTree_t>
bool vEBHeap<T,bits, vEBTree_t>::Member(unsigned int x)
{
  return tree.Member(x);
}

template <class T, int bits, class vEBTree_t>
vEBNode<T> vEBHeap<T,bits, vEBTree_t>::Predecessor(unsigned int x)
{
  auto index = tree.Predecessor(x);
  if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}

template <class T, int bits, class vEBTree_t>
void  vEBHeap<T,bits, vEBTree_t>::Insert(unsigned int x, T val)
{
  data[x] = val;
  tree.Insert(x);
}

template <class T, int bits, class vEBTree_t>
void  vEBHeap<T,bits, vEBTree_t>::Delete(unsigned int x)
{
  tree.Delete(x);
}

template <class T, int bits, class vEBTree_t>
vEBNode<T> vEBHeap<T,bits, vEBTree_t>::DeleteMin()
{
  auto index = tree.DeleteMin();
 if(index == -1)
  {
    return vEBNode<T>(index, T());
  }
  return vEBNode<T>(index, data[index]);
}
#endif