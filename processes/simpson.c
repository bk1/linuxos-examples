/* calculates the simpson integral of sin from A to B with N steps */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>


void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s A B N ID\n\n", argv0);
  printf("calculates integral from A to B of sin() with N steps\n");
  exit(1);
}

int main(int argc, char *argv[]) {
  if (argc != 5) {
    usage(argv[0], "wrong number of parameters");
  }

  const double A = atof(argv[1]);
  const double B = atof(argv[2]);
  const int N = atoi(argv[3]);

  if (A >= B) {
    usage(argv[0], "B must be > A");
  }
  if (N <= 0) {
    usage(argv[0], "N must be > 0");
  }

  const double delta = (B - A) / N;
  const double delta2 = delta / 2;
  
  double x = A;
  double result = 0.0;
  for (int i = 0; i < N; i++) {
    double contribution = 0.0;
    contribution += sin(x);
    x += delta2;
    contribution += 4 * sin(x);
    x += delta2;
    contribution += sin(x);
    contribution *= delta;
    contribution /= 6;
    result += contribution;
  }
  printf("pid=%8d ID=%-8s A=%8.6lf B=%8.6lf N=%8d -> result=%8.6f\n", getpid(), argv[4], A, B, N, result);
  exit(0);
}

