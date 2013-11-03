// vEB.cpp : Defines the entry point for the console application.
//

#include "bitsmartveb.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

int main(int argc, char* argv[])
{
  assert(sizeof(unsigned int)==4);

  /*
  vEBTree<16> tree;
  for(int i = 0; i < 1<<15; i++)
  {
    tree.Insert(i);
  }
  while(tree.Min() != -1)
  {
    cout << tree.DeleteMin() << endl;
  }
  */

  BitSmartvEBTree<24> tree;
  tree.Insert(89);
  tree.Insert(189);
  tree.Insert(289);
  tree.Insert(9);
  tree.Insert(8);

  tree.Delete(289);
  tree.Delete(9);
  
  cout << tree.Member(89) << endl;
  cout << tree.Member(189) << endl;
  cout << tree.Member(289) << endl;
  cout << tree.Member(9) << endl;
  cout << tree.Member(8) << endl;

  cout << tree.Min() << endl;
  cout << tree.Max() << endl;

  cout << tree.Predecessor(18) << endl;
  cout << tree.Predecessor(180) << endl;
  cout << tree.Predecessor(1800) << endl;
  cout << tree.Predecessor(1) << endl;

  // system("PAUSE");


	return 0;
}

