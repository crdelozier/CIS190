#include <cstdio>

int main() {
    bool TRUE = true;
    bool FALSE = false;

    if(true){
        printf("This statement should print!\n");
    }

    if(false){
        printf("This statement should not print.\n");
    }

    if(-500){
        printf("This statement should also print!\n");
    }

    printf("True: %d, False: %d\n",true, false);

    return 0;
}
