#include <cassert>
#include <iostream>

#include "array.hpp"

int main(){
  using namespace cis;
  array<long*> arr(10);
  array<int> arr2(5);

  array<bool> boolArray(16);

  arr2[0] = 2;

  long *x = new long;
  *x = 5;

  arr[2] = x;
  
  long *y = new long;
  y = arr[2];
  std::cout << *y << "\n";

  array<int> arr3(5);
  arr3.copyFrom(arr2);

  return 0;
}
