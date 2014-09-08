#include <stdio.h>

static int outer_c = 1000;

int non_static_outer_c = 2000;

int count() {
  static int c = 3000;
  return c++;
}

int count2() {
  return outer_c++;
}

int count3() {
  return non_static_outer_c++;
}

int non_count() {
  int c = 4000;
  return c++;
}

int main(int argc, char **argv) {
  int i;
  for (i = 0; i < 10; i++) {
    printf("i=%2d count=%d count2=%d count3=%d non_count=%d\n", i, count(), count2(), count3(), non_count());
  }
  return 0;
}
  

