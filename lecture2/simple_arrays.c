#include <stdio.h>

int main(void) {
    int arr [] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int i = 0;
    int arr2[10];

    char name[100];
    std::string name;

    int arr[10];
    std::vector<int> arr;

    for(i = 0; i < 10; i++) {
      arr2[i] = arr[i];
    }

    for (i = 0; i < 10; i++) {
        printf("%d\n", arr2[i]);
    }
    return 0;
}
