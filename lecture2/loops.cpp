#include <stdio.h>

int main() {
    for(int c = 10; c > 0; c--){
        printf("%d,",c);
    }
    printf("\n");


    int d = 10;
    while(d){
        printf("%d,",d);
        d--;
    }
    printf("\n");

    int e = 10;
    do{
        printf("%d,",e);
        e--;
    }while(e);
    printf("\n");

    return 0;
}
