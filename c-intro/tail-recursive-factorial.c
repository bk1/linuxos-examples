#include <stdio.h>


unsigned long long fac(int n);

unsigned long long fac_intern(int n, unsigned long long akk);

double dfac(int n);

double dfac_intern(int n, double akk);

int main(int argc, char *argv[]) {
  int n;
  for (n = 0; n < 180; n++) {
    unsigned long long f = fac(n);
    double df = dfac(n);
    printf("n=%10d f=%30llu df=%30e\n", n, f, df);
    if (f == 0 && df == 0) {
      break;
    }
  }
  return 0;
}

unsigned long long fac(int n) {
  return fac_intern(n, 1);
}

unsigned long long fac_intern(int n, unsigned long long akk) {
  if (n <= 1) {
    return akk;
  } else {
    return fac_intern(n - 1, akk * n);
  }
}

double dfac(int n) {
  return dfac_intern(n, 1);
}

double dfac_intern(int n, double akk) {
  if (n <= 1) {
    return akk;
  } else {
    return dfac_intern(n - 1, akk * n);
  }
}
