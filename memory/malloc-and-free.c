#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s <number> <summand> <factor>\n\n", argv0);
  printf("allocates number pieces of memory of sizes 1..number");
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    usage(argv[0], "wrong number of arguments");
  }
  int cnt_i = atoi(argv[1]);
  if (cnt_i <= 0) {
    usage(argv[0], "number must be positive");
  }
  char buffer[1024];
  size_t cnt = (size_t) cnt_i;
  void *prev = NULL;
  void *pprev = NULL;
  size_t size = 1;
  int summand = atoi(argv[2]);
  void *base = malloc(1);
  void *pbase = base;
  double factor = atof(argv[3]);

  printf("cnt=%zd summand=%d factor=%f\n", cnt, summand, factor);

  for (int i = 0; i < cnt; i++) {
    void *ptr = malloc(size);
    free(pprev);
    pprev = prev;
    prev = ptr;
    int rel = (int) (ptr - base);
    int diff = (int) (ptr - pbase);
    pbase = ptr;
    size_t *isize = (size_t *) (ptr - 8);
    sprintf(buffer, "i=%d s=%zd rel=%d diff=%d isize=%zd\n", i, size, rel, diff, *isize);
    write(1, buffer, strlen(buffer));
    size = (size_t) (summand + factor * size);
  }
  exit(0);
}
