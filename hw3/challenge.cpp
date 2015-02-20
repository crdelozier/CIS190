#include <iostream>
#include <string>

class FloatVector{
  int x;
  int y;
  int z;

public:
  FloatVector(int _x, int _y, int _z) : x(_x), y(_y), z(_z){}

  int operator[] (int index){
    int *arr = &x;
    return arr[index];
  }

  FloatVector& copySelf(){
    this->x = 5;
    return *this;
  }
};

void f(int **ptp){
  // PRINT y (from the main function) HERE
  
}

int main(){
  FloatVector fv(1,2,3);

  std::cout << fv[1] << "\n";

  int x = 1;
  std::string s;
  int y = 2;
  int *p = &x;

  f(&p);

  return 0;
}
