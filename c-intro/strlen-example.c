#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage %s string\n", argv[0]);
    return 1;
  } else {
    size_t len = strlen(argv[1]);
    printf("strlen(%s)=%lu\n", argv[1], (unsigned long) len);
    printf("strlen(%s)=%zu\n", argv[1], len);
  }
  return 0;
}
