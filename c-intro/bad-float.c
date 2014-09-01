#include <stdio.h>

int main(int argc, char *argv[]) {
  double x = 1.0e-15;
  double y = 1.0L;
  double z = x+y;
  double zz = z - y;
  printf("x=%le y=%le z=%le zz=%le\n", x, y, z, zz);
  x = 1.0e-16;
  y = 1.0L;
  z = x+y;
  zz = z - y;
  printf("x=%le y=%le z=%le zz=%le\n", x, y, z, zz);
  double u = 1.0L;
  double v = 1.00000000000001L;
  double w = (v - u) * 100000000000000.0L;
  printf("u=%le v=%le w=%le\n", u, v, w);
  return 0;
}
