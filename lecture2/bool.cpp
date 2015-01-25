#include <stdio.h>

int main() {
    int TRUE = 1;
    int FALSE = 0;

    if(TRUE){
        printf("This statement should print!\n");
    }

    if(FALSE){
        printf("This statement should not print.\n");
    }

    if(-500){
        printf("This statement should also print!\n");
    }

    printf("True: %d, False: %d\n",10 == 10, 2 == 5);

    return 0;
}
