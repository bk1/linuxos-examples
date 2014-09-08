#include <stdio.h>

static int si = 1;
const int ci = 2;
static const int sci = 3;
int gi = 4;

int count() {
  static int c = 0;
  return c++;
}

int main(int argc, char **argv) {
  print("count=%d count=%d count=%d\n", count(), count(), count());
  

