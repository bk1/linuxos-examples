#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s\n\n", argv0);
  printf("allocates pieces of memory of different sizes\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 1) {
    usage(argv[0], "wrong number of arguments");
  }
  int sizes[] = { 24, 248, 24, 56, 24, 1016, 24 };
  void *ptrs[7];
  int n = 7;
  int i;
  for (i = 0; i < n; i++) {
    ptrs[i] = malloc(sizes[i]);
  }
  for (i = 1; i < n; i+=2) {
    free(ptrs[i]);
  }
  void *ptr = malloc(56);
  for (i = 0; i < n; i++) {
    if (ptr == ptrs[i]) {
      printf("matches i=%d size=%d\n", i, sizes[i]);
      if (i == 1) {
        printf("first-fit\n");
      } else if (i == 3) {
        printf("best-fit\n");
      } else if (i == 5) {
        printf("worst-fit\n");
      } else {
        printf("unknown\n");
      }
    }
  }
  exit(0);
}
