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
      printf("This should also print\n");
    }
    
    printf("True: %d, False: %d\n",1==1,1!=1);

    return 0;
}
