#include <iostream>

int main(){
  unsigned long y = 0;
  unsigned long x = (unsigned long)&y;

  x |= 1;

  std::cout << "x: " << x << "\n";

  unsigned long *p = (unsigned long*)x;

    *p = 1;

    std::cout << y << "\n";

    return 0;
}
