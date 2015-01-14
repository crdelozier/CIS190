#include <stdio.h>

void f(unsigned int y){
  printf("Value: %d\n",y);
}

int main(void){
  int x = -1; // User input
  unsigned int y = x;

  f(x);
  f(y);

  return 0;
}
