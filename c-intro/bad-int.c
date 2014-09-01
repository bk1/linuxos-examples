#include <stdio.h>

int main(int argc, char *argv[]) {
  int x = 0x7fffffff;
  printf("x=%d x+x=%d\n", x, x+x);
  signed short y = 0x7fff;
  signed short yy = y+y;
  printf("y=%d y+y=%d\n", y, yy);
  long z = 0x7fffffffffffffffL;
  printf("z=%ld z+z=%ld\n", z, z+z);
  return 0;
}
