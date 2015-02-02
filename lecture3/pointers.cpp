#include <iostream>

int main(){
    int x = 0;
    int *p = &x;

    *p = 1;

    std::cout << x << "\n";

    return 0;
}
