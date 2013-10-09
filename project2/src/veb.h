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

class vEBTree
{
private:
  unsigned int bits;
  unsigned int min;
  unsigned int max;
  vEBTree * top;
  vEBTree ** bottom;
  void emptyInsert(unsigned int x);
public:
  unsigned int Min() { return min; }
  unsigned int Max() { return max; }
  vEBTree(unsigned int b);
  ~vEBTree();
  bool Member(unsigned int x);
  unsigned int Predecessor(unsigned int x);
  void Insert(unsigned int x);
  void Delete(unsigned int x);
  unsigned int DeleteMin();
};

vEBTree::vEBTree(unsigned int b) : bits(b), min(-1), max(-1) 
{
  if(bits!=1)
  {
    top = new vEBTree(b/2);
    bottom = new vEBTree*[1<<(b/2)];
    for(int i = 0; i < 1<<(b/2); i++)
    {
      bottom[i] = new vEBTree(halfUp(b));
    }
  }
}

vEBTree::~vEBTree()
{
  if(bits==1) return;

  delete top;
  for(int i = 0; i < 1<<(bits/2); i++)
  {
    delete bottom[i];
  }
  delete bottom;
}

bool vEBTree::Member(unsigned int x)
{
  assertLimit(x, bits);
  if(x == min || x == max)
    return true;
  else if (bits == 1)
    return false;
  else return bottom[high(x, bits)]->Member(low(x, bits));
}

unsigned int vEBTree::Predecessor(unsigned int x)
{
  assertLimit(x, bits);
  if(bits == 1)
  {
    if(x ==1 && min == 0)
    {
      return 0;
    }
    else return -1;
  }
  else if(max != -1 && x > max)
  {
    return max;
  }
  else 
  {
    auto min_low = bottom[high(x,bits)]->Min();
    if(min_low != -1 && low(x,bits) > min_low)
    {
      auto offset = bottom[high(x,bits)]->Predecessor(low(x, bits));
      return value(high(x, bits), offset, bits);
    }
    else
    {
      auto low_tree = top->Predecessor(high(x, bits));
      if(low_tree == -1)
      {
        if(min != -1 && x > min)
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

void vEBTree::emptyInsert(unsigned int x)
{
  assert(min == -1);
  min = max = x;
}

void vEBTree::Insert(unsigned int x)
{
  assertLimit(x, bits);
  if(min == -1)
  {
    emptyInsert(x);
    return;
  }
  if(x < min)
  {
    auto tmp = x;
    x = min;
    min = tmp;
  }
  if(bits != 1)
  {
    if(bottom[high(x,bits)]->Min() == -1)
    {
      top->Insert(high(x,bits));
      bottom[high(x,bits)]->emptyInsert(low(x,bits));
    }
    else
    {
      bottom[high(x,bits)]->Insert(low(x,bits));
    }
  }
  if(x>max)
  {
    max = x;
  }
}

void vEBTree::Delete(unsigned int x)
{
  assert(Member(x));
  assertLimit(x, bits);
  if(min==max)
  {
    min = max = -1;
    return;
  }
  if(bits == 1)
  {
    if(x == 0)
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
  if(x==min)
  {
    auto low_tree = top->Min();
    x = value(low_tree, bottom[low_tree]->Min(), bits);
    min = x;
  }
  bottom[high(x,bits)]->Delete(low(x,bits));
  if(bottom[high(x,bits)]->Min() == -1)
  {
    top->Delete(high(x, bits));
    if(x == max)
    {
      auto high_tree = top->Max();
      if(high_tree == -1)
      {
        max = min;
      }
      else
      {
        max = value(high_tree, bottom[high_tree]->Max(), bits);
      }
    }
  }
  else if(x == max)
  {
    max = value(high(max, bits), bottom[high(x,bits)]->Max(), bits);
  }

}

unsigned int vEBTree::DeleteMin()
{
  assert(min != -1);
  auto res = min;
  Delete(res);
  return res;
}

#endif