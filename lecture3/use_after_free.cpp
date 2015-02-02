#include <iostream>

int main(){
    int *p = new int;
    delete p;

    int *p2 = new int;
    *p2 = 6;

    *p = 5;

    std::cout << *p2 << "\n";

    return 0;
}
