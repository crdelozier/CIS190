#include <stdio.h>

int main(void) {
    int arr [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int i;

    // TODO: Add another (uninitialized) array and assign arr's elements into it

    for (i = 0; i < 10; i++) {
        printf("%d\n", arr[i]);
    }
    return 0;
}
