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
  auto veb = new vEBTree<16>();
  veb->Insert(67);
  veb->Insert(7);
  veb->Insert(12);
  veb->Insert(3323);
  veb->Insert(11132);
  veb->Insert(13112);
  veb->Insert(11212);
  veb->Insert(11122);
  veb->Insert(7133);
  veb->Insert(132);
  veb->Insert(33112);
  veb->Insert(312);
  veb->Insert(12122);
  veb->Insert(71);
  veb->Insert(122);
  veb->Delete(12);
  veb->Insert(16);
  cout << veb->Predecessor(40000) << "\n";
  cout << veb->Predecessor(86) << "\n";
  veb->Delete(67);
  cout << veb->Predecessor(86)<< "\n";;
  veb->Delete(7);
  while(veb->Min() != -1)
  {
    cout << veb->DeleteMin() << "\n";;
  }
  system("PAUSE");
  delete veb;

	return 0;
}

