#include <stdio.h>
#include <string.h>

int main(){
    char str[] = "Hello"; // == {'H','e','l','l','o','\0'};
    char str2[] = "Hello";

    printf("%s\n",str);
    printf("%s\n",str2);

    printf("%d\n",str == str2); // 0 (false)
    printf("%d\n",str != str2); // 1 (true)

    printf("%d\n",strcmp(str,str2) == 0); // 1 (true)

    return 0;
}
