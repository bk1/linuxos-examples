#include <stdio.h>
#include <stdlib.h>

void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s <number>\n\n", argv0);
  printf("allocates number pieces of memory of sizes 1..number");
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage(argv[0], "wrong number of arguments");
  }
  int cnt_i = atoi(argv[1]);
  if (cnt_i <= 0) {
    usage(argv[0], "number must be positive");
  }
  size_t cnt = (size_t) cnt_i;
  void **ptrs = (void **) malloc(cnt * sizeof(void *));
  for (int i = 0; i < cnt; i++) {
    ptrs[i] = malloc(i+1);
  }
  void *prev = ptrs[0];
  void *first = ptrs[0];
  for (int i = 0; i < cnt; i++) {
    void *ptrs_i = ptrs[i];
    int rel = (int) (ptrs_i - first);
    int diff = (int) (ptrs_i - prev);
    prev = ptrs_i;
    int *ptr8 = (int *) (ptrs_i - 8);
    int *ptr4 = (int *) (ptrs_i - 4);
    long *lptr8 = (long *) (ptrs_i - 8);
    printf("i=%8d r=%8d d=%8d p8l=%8ld p8=%8d p4=%8d\n", i, rel, diff, *lptr8, *ptr8, *ptr4);
    // free(ptrs_i);
    // printf("i=%8d freed: p8=%8d p4=%8d\n", i, *ptr8, *ptr4);
    
  }
  exit(0);
}
