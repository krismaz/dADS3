#ifndef VEB_H
#define VEB_H

//Note -1 is uinsigned max, HAXXOR aka nil
//Note high bits are the small segment
//Note Cormen er gud!

#include <assert.h>

#define halfUp(x) (x/2+x%2)
#define assertLimit(x,b) assert(x < (1<<b));

unsigned int high(unsigned int n, unsigned int bits)
{
  assertLimit(n, bits);
  return n >> halfUp(bits);
}

unsigned int low(unsigned int n, unsigned int bits)
{
  assertLimit(n,bits);
  return n & ((1 << halfUp(bits))-1);
}

unsigned int value(unsigned int high, unsigned int low, unsigned int bits)
{
  assertLimit(high, bits);
  assertLimit(low, halfUp(bits));
  return low | (high << (bits/2+bits%2));
}

template <int bits>
class vEBTree
{
private:
  unsigned int min;
  unsigned int max;
  vEBTree<bits/2> * top;
  vEBTree<halfUp(bits)> ** bottom;
public:
  void emptyInsert(unsigned int x);
  unsigned int Min() { return min; }
  unsigned int Max() { return max; }
  vEBTree();
  ~vEBTree();
  bool Member(unsigned int x);
  unsigned int Predecessor(unsigned int x);
  void Insert(unsigned int x);
  void Delete(unsigned int x);
  unsigned int DeleteMin();
};

static unsigned long long comparisonCount = 0;

template <int bits>
vEBTree<bits>::vEBTree() : min(-1), max(-1) 
{
  if(bits!=1)
  {
    top = new vEBTree<bits/2>();
    bottom = new vEBTree<halfUp(bits)>*[1<<(bits/2)];
    for(int i = 0; i < 1<<(bits/2); i++)
    {
      bottom[i] = new vEBTree<halfUp(bits)>();
    }
  }
}

template <int bits>
vEBTree<bits>::~vEBTree()
{
  if(bits==1) return;

  delete top;
  for(int i = 0; i < 1<<(bits/2); i++)
  {
    delete bottom[i];
  }
  delete bottom;
}

template <int bits>
bool vEBTree<bits>::Member(unsigned int x)
{
  assertLimit(x, bits);
  if((++comparisonCount && x == min) || (++comparisonCount && x == max))
    return true;
  else if (++comparisonCount && bits == 1)
    return false;
  else return bottom[high(x, bits)]->Member(low(x, bits));
}

template <int bits>
unsigned int vEBTree<bits>::Predecessor(unsigned int x)
{
  assertLimit(x, bits);
  if(++comparisonCount && bits == 1)
  {
    if((++comparisonCount && x == 1) && (++comparisonCount && min == 0))
    {
      return 0;
    }
    else return -1;
  }
  else if((++comparisonCount && max != -1) && (++comparisonCount && x > max))
  {
    return max;
  }
  else 
  {
    auto min_low = bottom[high(x,bits)]->Min();
    if((++comparisonCount && min_low != -1) && (++comparisonCount && low(x,bits) > min_low))
    {
      auto offset = bottom[high(x,bits)]->Predecessor(low(x, bits));
      return value(high(x, bits), offset, bits);
    }
    else
    {
      auto low_tree = top->Predecessor(high(x, bits));
      if(++comparisonCount && low_tree == -1)
      {
        if((++comparisonCount && min != -1) && (++comparisonCount && x > min))
        {
          return min;
        }
        return -1;
      }
      else
      {
        auto offset = bottom[low_tree]->Max();
        return value(low_tree, offset, bits);
      }
    }
  }
}

template <int bits>
void vEBTree<bits>::emptyInsert(unsigned int x)
{
  assert(min == -1);
  min = max = x;
}

template <int bits>
void vEBTree<bits>::Insert(unsigned int x)
{
  assert(!Member(x));
  assertLimit(x, bits);
  if(++comparisonCount && min == -1)
  {
    emptyInsert(x);
    return;
  }
  if(++comparisonCount && x < min)
  {
    auto tmp = x;
    x = min;
    min = tmp;
  }
  if(bits != 1) //optimized out
  {
    if(++comparisonCount && bottom[high(x,bits)]->Min() == -1)
    {
      top->Insert(high(x,bits));
      bottom[high(x,bits)]->emptyInsert(low(x,bits));
    }
    else
    {
      bottom[high(x,bits)]->Insert(low(x,bits));
    }
  }
  if(++comparisonCount && x > max)
  {
    max = x;
  }
}

template <int bits>
void vEBTree<bits>::Delete(unsigned int x)
{
  assert(Member(x));
  assertLimit(x, bits);
  if(++comparisonCount && min == max)
  {
    min = max = -1;
    return;
  }
  if(bits == 1) //optimized out
  {
    if(++comparisonCount && x == 0)
    {
      min = 1;
    }
    else
    {
      min = 0;
    }
    max = min;
    return;
  }
  if(++comparisonCount && x == min)
  {
    auto low_tree = top->Min();
    x = value(low_tree, bottom[low_tree]->Min(), bits);
    min = x;
  }
  bottom[high(x,bits)]->Delete(low(x,bits));
  if(++comparisonCount && bottom[high(x,bits)]->Min() == -1)
  {
    top->Delete(high(x, bits));
    if(++comparisonCount && x == max)
    {
      auto high_tree = top->Max();
      if(++comparisonCount && high_tree == -1)
      {
        max = min;
      }
      else
      {
        max = value(high_tree, bottom[high_tree]->Max(), bits);
      }
    }
  }
  else if(++comparisonCount && x == max)
  {
    max = value(high(max, bits), bottom[high(x,bits)]->Max(), bits);
  }

}

template <int bits>
unsigned int vEBTree<bits>::DeleteMin()
{
  assert(min != -1);
  auto res = min;
  Delete(res);
  return res;
}

#endif