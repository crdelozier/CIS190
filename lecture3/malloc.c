#include <cstdlib>
#include <iostream>
#include <cassert>

// int *p; *p = 1;
// void* malloc(size_t size);
// void free(void *p);

int main(){
  //int *p = (int*)malloc(sizeof(int));
  int *p = new int;
    assert(p != nullptr);
    //int *a = (int*)malloc(10 * sizeof(int));
    int *a = new int[10];
    assert(a != nullptr);
    int c = 0;

    for(c = 0; c < 10; c++){
        a[c] = c;
    }

    for(c = 0; c < 10; c++){
        *p += a[c];
    }

    std::cout << *p << "\n";

    //free(p);
    delete p;
    //free(a);
    delete [] a;

    return 0;
}
