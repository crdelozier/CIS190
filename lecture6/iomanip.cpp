#include <iostream>
#include <iomanip>

int main(){
  std::cout << std::setfill('0') << std::setw (5);
  std::cout << 1 << ".tmp" << std::endl;
  std::cout << 2 << ".tmp" << std::endl;
  return 0;
}
