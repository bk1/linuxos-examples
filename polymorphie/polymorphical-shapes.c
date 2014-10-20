/* calculates the area and circumference of shapes */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>

void usage(char *argv0, char *text) {
  printf("%s\n", text);
  printf("\n\nUsage:\n\n%s S1 S2 S3 S4 ... Sn\n\n", argv0);
  printf("calculates n random shapes. Si can be C for circle, S for square or T for triangle, respectively\n");
  exit(1);
}

struct shape_data;

typedef double (*fun)(struct shape_data *data);
typedef void (*proc)(struct shape_data *data);

struct shape_data {
  proc printer;
  fun circumference;
  fun area;
  double a; /* also used as r for circles */
  double b;
  double c;
};

double c_to_d(char c) {
  return (double) (c-'0');
}

double random_double() {
  return (abs(random()) + 1) / 1000000.0;
}

double area(struct shape_data *data) {
  return data->area(data);
}

double circumference(struct shape_data *data) {
  return data->circumference(data);
}

void printer(struct shape_data *data) {
  data->printer(data);
}

double circle_area(struct shape_data *data) {
  double r = data->a;
  return M_PI*r*r;
}

double circle_circumference(struct shape_data *data) {
  double r = data->a;
  return 2*M_PI*r;
}

void circle_printer(struct shape_data *data) {
  printf("C(r=%f)", data->a);
}

void circle_init(struct shape_data *data, double r) {
  data->area=circle_area;
  data->circumference=circle_circumference;
  data->printer=circle_printer;
  data->a = r;
  data->b = 0;
  data->c = 0;
}

void circle_random_init(struct shape_data *data) {
  double r = random_double();
  circle_init(data, r);
}


double square_area(struct shape_data *data) {
  double a = data->a;
  return a*a;
}

double square_circumference(struct shape_data *data) {
  double a = data->a;
  return 4 * a;
}

void square_printer(struct shape_data *data) {
  printf("S(a=%f)", data->a);
}

void square_init(struct shape_data *data, double a) {
  data->area=square_area;
  data->circumference=square_circumference;
  data->printer=square_printer;
  data->a = a;
  data->b = 0;
  data->c = 0;
}

void square_random_init(struct shape_data *data) {
  double a = random_double();
  square_init(data, a);
}


double triangle_area(struct shape_data *data) {
  double a = data->a;
  double b = data->b;
  double c = data->c;
  double s = (a+b+c)/2;
  double tarea = sqrt(s*(s-a)*(s-b)*(s-c));
  return tarea;
}

double triangle_circumference(struct shape_data *data) {
  double a = data->a;
  double b = data->b;
  double c = data->c;
  return a+b+c;
}

void triangle_printer(struct shape_data *data) {
  double a = data->a;
  double b = data->b;
  double c = data->c;
  printf("T(a=%f b=%f c=%f)", a, b, c);
}

void triangle_init(struct shape_data *data, double a, double b, double c) {
  data->area=triangle_area;
  data->circumference=triangle_circumference;
  data->printer=triangle_printer;
  data->a = a;
  data->b = b;
  data->c = c;
}

void triangle_random_init(struct shape_data *data) {
  double u = random_double();
  double v = random_double();
  double w = random_double();
  double a = u+v;
  double b = v+w;
  double c = u+w;
  triangle_init(data, a, b, c);
}

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    usage(argv[0], "no arguments");
  }
  char **argx = argv+1;
  size_t cnt = (size_t) (argc - 1);
  double total_circumference = 0.0;
  double total_area = 0.0;
  struct shape_data *array = (struct shape_data *) malloc(cnt * sizeof(struct shape_data));
  for (int i = 0; i < cnt; i++) {
    char *arg = argx[i];
    size_t l = strlen(arg);
    if (l < 1 || l > 4) {
      usage(argv[0], "strlen of each argument must be 1..4");
    }
    char c = arg[0];
    switch (c) {
    case 'C':
      if (l == 1) {
        circle_random_init(&(array[i]));
      } else if (l == 2) {
        circle_init(&(array[i]), c_to_d(arg[1]));
      } else {
        usage(argv[0], "strlen for C must be 1 or 2");
      }
      break;
    case 'S':
      if (l == 1) {
        square_random_init(&(array[i]));
      } else if (l == 2) {
        square_init(&(array[i]), c_to_d(arg[1]));
      } else {
        usage(argv[0], "strlen for S must be 1 or 2");
      }
      break;
    case 'T':
      if (l == 1) {
        triangle_random_init(&(array[i]));
      } else if (l == 4) {
        triangle_init(&(array[i]), c_to_d(arg[1]), c_to_d(arg[2]), c_to_d(arg[3]));
      } else {
        usage(argv[0], "strlen for T must be 1 or 4");
      }
      break;
    default: usage(argv[0], "only C S and T allowed");
      break;
    }
    printf("%3d shape=", i);
    array[i].printer(&array[i]);
    double my_area = area(&array[i]);
    double my_circumference = circumference(&array[i]);
    printf(" A=%f U=%f\n", my_area, my_circumference);
    total_area += my_area;
    total_circumference += my_circumference;
  }
  printf("\ntotal A=%f U=%f\n", total_area, total_circumference);
}
