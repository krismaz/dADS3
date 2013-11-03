#ifndef BITSMARTVEB_H
#define BITSMARTVEB_H

#include <iostream>
using namespace std;

//Magical Bit based vEB tree. Whenever we hit a tree that can bee stored in 32-bit integers, just use bitwise operation on an uint32 instead. Might be faster,and saves a truckload of memory

#ifdef _WIN32
#include <intrin.h> //Someone should find the one for lunix
#define msb unsigned long res = 0; _BitScanReverse(&res,mask);
#define lsb unsigned long res = 0; _BitScanForward(&res,mask);
#endif

#ifndef _WIN32
#define msb unsigned int res = __builtin_clz(mask)^0x1F; //http://sourceforge.net/p/mingw-w64/bugs/322/
#define lsb unsigned int res = __builtin_ctz(mask);
#endif

#include "veb.h"
void BitSmartInsert(unsigned int &mask, unsigned int value)
{
  mask = mask | (1<<value);
}

void BitSmartDelete(unsigned int &mask, unsigned int value)
{
  mask = mask & ((-1) ^ (1<<value));
}


bool BitSmartMember(unsigned int mask, unsigned int value)
{
  return (mask & (1<<value))!=0;
}

unsigned int BitSmartPredecessor(unsigned int mask, unsigned int value)
{
  if(mask == 0) return -1;
  mask = mask & ((1<<value)-1);
  msb
  return res;
}

unsigned int BitSmartMax(unsigned int mask)
{
  if(mask == 0) return -1;
  msb
  return res;
}

unsigned int BitSmartMin(unsigned int mask)
{
  if(mask == 0) return -1;
  lsb
  return res;
}


template <int bits>
class BitSmartvEBTree
{
private:
  unsigned int min;
  unsigned int max;
  union
  {
    BitSmartvEBTree<bits/2> * top;
    unsigned int mask;
  };
  BitSmartvEBTree<halfUp(bits)> ** bottom;
public:
  void emptyInsert(unsigned int x);
  unsigned int Min() 
  { 
    if(bits<=5)
    {
      return BitSmartMin(mask);
    }
    return min; 
  }
  unsigned int Max() 
  { 
    if(bits<=5)
    {
      return BitSmartMax(mask);
    }
    return max; 
  }
  BitSmartvEBTree();
  ~BitSmartvEBTree();
  bool Member(unsigned int x);
  unsigned int Predecessor(unsigned int x);
  void Insert(unsigned int x);
  void Delete(unsigned int x);
  unsigned int DeleteMin();
};

template <int bits>
BitSmartvEBTree<bits>::BitSmartvEBTree() : min(-1), max(-1), mask(0)
{
  if(bits>5)
  {
    top = new BitSmartvEBTree<bits/2>();
    bottom = new BitSmartvEBTree<halfUp(bits)>*[1<<(bits/2)];
    for(int i = 0; i < 1<<(bits/2); i++)
    {
      bottom[i] = new BitSmartvEBTree<halfUp(bits)>();
    }
  }
}

template <int bits>
BitSmartvEBTree<bits>::~BitSmartvEBTree()
{
  if(bits<=5) return;

  delete top;
  for(int i = 0; i < 1<<(bits/2); i++)
  {
    delete bottom[i];
  }
  delete bottom;
}

template <int bits>
bool BitSmartvEBTree<bits>::Member(unsigned int x)
{
  assertLimit(x, bits);
  if (bits <=5)
    return BitSmartMember(mask, x);
  else if (x == min || x == max)
    return true;
  else return bottom[high(x, bits)]->Member(low(x, bits));
}

template <int bits>
unsigned int BitSmartvEBTree<bits>::Predecessor(unsigned int x)
{
  assertLimit(x, bits);
  if(bits <= 5)
  {
    return BitSmartPredecessor(mask, x);
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

template <int bits>
void BitSmartvEBTree<bits>::emptyInsert(unsigned int x)
{
  if(bits <= 5)
  {
    BitSmartInsert(mask,x);
    return;
  }
  assert(min == -1);
  min = max = x;
}

template <int bits>
void BitSmartvEBTree<bits>::Insert(unsigned int x)
{
  assert(!Member(x));
  assertLimit(x, bits);
  if(bits <= 5)
  {
    BitSmartInsert(mask,x);
    return;
  }
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

template <int bits>
void BitSmartvEBTree<bits>::Delete(unsigned int x)
{
  assert(Member(x));
  assertLimit(x, bits);
  if(bits <= 5)
  {
    BitSmartDelete(mask, x);
    return;
  }
  if(min==max)
  {
    min = max = -1;
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

template <int bits>
unsigned int BitSmartvEBTree<bits>::DeleteMin()
{
  assert(min != -1);
  auto res = Min();
  Delete(res);
  return res;
}

#endif