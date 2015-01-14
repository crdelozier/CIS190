#include <stdlib.h>
#include <stdio.h>

// char*
// int main () {
int main(int argc, char **argv) { // public static void main(String [] args) {
  if (argc == 2) {
    int val = atoi(argv[1]);
    if (val == 100) {
      printf("That's a good number!\n");
    } else {
      printf("%d is a bad number! Do not enter %d!\n", val, val);
    }
  }else{
    printf("Usage: %s [number]\n",argv[0]);
  }
  return 0;
}
