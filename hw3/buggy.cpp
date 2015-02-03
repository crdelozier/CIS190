#include <iostream>
#include <cstdlib>

void vectorAdd(int *a, int *b, int *c, int vectorSize){
  for(int i = 0; i < vectorSize; i++){
    c[i] = a[i] + b[i];
  }
}

void vectorSum(int *sum, int *v, int vectorSize){
  for(int i = 0; i < vectorSize; i++){
    *sum += v[i];
  }
}

int main(){
  int vectorSize = 5;
  int *p;
  int *a = new int[vectorSize];
  int *b = new int[vectorSize];
  int *c = new int[vectorSize];

  if(p == nullptr){
    p = new int;
  }

  for(int i = 0; i < 6; i++){
    a[i] = rand() % 100;
    b[i] = rand() % 100;
    c[i] = 0;
  }

  vectorSum(p,a,vectorSize);
  std::cout << "Sum of a: " << *p << "\n";

  p = new int;
  *p = 0;

  vectorSum(p,b,vectorSize);
  delete p;
  std::cout << "Sum of b: " << *p << "\n";

  delete [] a;
  delete [] b;
  delete [] c;

  return 0;
}
