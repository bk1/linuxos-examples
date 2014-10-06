/* calculates the simpson integral of sin from A to B with N steps */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s F A B N ID\n\n", argv0);
  printf("calculates integral of F from A to B of F() with N steps\n");
  printf("F must be one of sin cos tan cot sec csc exp log sqr cub\n");
  exit(1);
}

typedef double (*fun)(const double x);

struct int_data {
  fun function;
  double a;
  double b;
  int n;
};

double cot(double x) {
  return cos(x)/sin(x);
}
double sec(double x) {
  return 1/cos(x);
}
double csc(double x) {
  return 1/sin(x);
}
double sqr(double x) {
  return x*x;
}
double cub(double x) {
  return x*x*x;
}

double simpson(struct int_data *data) {
  double A = data->a;
  double B = data->b;
  double N = data->n;
  const double delta = (B - A) / N;
  const double delta2 = delta / 2;
  
  double x = A;
  double result = 0.0;
  for (int i = 0; i < N; i++) {
    double contribution = 0.0;
    contribution += data->function(x);
    x += delta2;
    contribution += 4 * data->function(x);
    x += delta2;
    contribution += data->function(x);
    contribution *= delta;
    contribution /= 6;
    result += contribution;
  }
  return result;
}    

int main(int argc, char *argv[]) {
  if (argc != 6) {
    usage(argv[0], "wrong number of parameters");
  }
  printf("function=%s\n", argv[1]);

  struct timeval tv;
  gettimeofday(&tv, NULL);
  long t0 = 1000000L * tv.tv_sec + tv.tv_usec;
  const double A = atof(argv[2]);
  const double B = atof(argv[3]);
  const int N = atoi(argv[4]);

  if (A >= B) {
    usage(argv[0], "B must be > A");
  }
  if (N <= 0) {
    usage(argv[0], "N must be > 0");
  }
  printf("started: pid=%8d ID=%-8s A=%8.6lf B=%8.6lf N=%8d\n\n", getpid(), argv[5], A, B, N);

  struct int_data data;
  data.a = A;
  data.b = B;
  data.n = N;
  if (strcmp(argv[1], "sin") == 0) {
    data.function = sin;
  } else if (strcmp(argv[1], "cos") == 0) {
    data.function = cos;
  } else if (strcmp(argv[1], "tan") == 0) {
    data.function = tan;
  } else if (strcmp(argv[1], "cot") == 0) {
    data.function = cot;
  } else if (strcmp(argv[1], "sec") == 0) {
    data.function = sec;
  } else if (strcmp(argv[1], "csc") == 0) {
    data.function = csc;
  } else if (strcmp(argv[1], "exp") == 0) {
    data.function = exp;
  } else if (strcmp(argv[1], "log") == 0) {
    data.function = log;
  } else if (strcmp(argv[1], "sqr") == 0) {
    data.function = sqr;
  } else if (strcmp(argv[1], "cub") == 0) {
    data.function = cub;
  } else {
    usage(argv[0], "unknown function");
  }
  printf("function=%s\n", argv[1]);
  double result = simpson(&data);
  gettimeofday(&tv, NULL);
  long t1 = 1000000L * tv.tv_sec + tv.tv_usec;
  long delta_t = t1 - t0;
  printf("pid=%8d ID=%-8s t=%8ld A=%8.6lf B=%8.6lf N=%8d -> result=%8.6f\n\n", getpid(), argv[4], delta_t, A, B, N, result);
  exit(0);
}

