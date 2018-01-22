// g++ main.cpp  -std=c++11 -g -o watchpoint_app

// gdb watchpoint_app
// break main.cpp: 9
// r
// watch array[10]
// c
// .. watchpoint works - we now where's the bug

#include <iostream>

int main(int, char *[])
{
  constexpr int SIZE = 20;
  int array[SIZE] = {0};

  std::cout << "Started filling array\n";
  // we want to fill first 10 elements with ascending numbers
  for (int idx = 0; idx <= 10; ++idx) // ups
  {
    array[idx] = idx;
  }

  // .... many lines later....

  for (int idx = 0; idx < SIZE; ++idx)
  {
    std::cout << array[idx]<< " ";
  }
  std::cout << "\n";

  // Why first 11 elements are set?!" << std::endl;
}
