#include <iostream>

int main(){
    int **ptp = new int*;
    int *p1 = new int;
    int *p2 = new int;

    *p1 = 1;
    *p2 = 2;

    *ptp = p1;
    *ptp = p2;
    
    std::cout << "Address: " << *ptp << ", Value: " << **ptp << "\n";

    delete ptp;
    delete p1;
    delete p2;

    return 0;
}
