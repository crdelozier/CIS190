#include <iostream>

double f(){
  return 3.5;
}

int main(){
  int x = 5;
  auto y = x;
  auto z = f();
  // Some code in between
  auto result = y + z;
  std::cout << result << "\n";
  return 0;
}
