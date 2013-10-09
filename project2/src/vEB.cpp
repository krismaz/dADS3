// vEB.cpp : Defines the entry point for the console application.
//

#include "veb.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  //cout << value(high(379,9),low(379,9),9);
  auto veb = new vEBTree(9);
  veb->Insert(67);
  veb->Insert(7);
  veb->Insert(12);
  veb->Delete(12);
  veb->Insert(16);
  veb->Delete(67);
  veb->Delete(7);
  cout << veb->DeleteMin();
  cout << veb->DeleteMin();
  system("PAUSE");
  delete veb;

	return 0;
}

