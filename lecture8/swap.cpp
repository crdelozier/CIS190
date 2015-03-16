#include <iostream>

template<class T> void swap(T &lhs, T &rhs){
  T tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

int main(){
  int x = 1;
  int y = 2;

  float c = 2.5;
  float d = 3.4;

  swap<int>(x,y);
  swap<float>(c,d);

  std::cout << "x: " << x << ", y: " << y << "\n";
  std::cout << "c: " << c << ", d: " << d << "\n";

  return 0;
}
