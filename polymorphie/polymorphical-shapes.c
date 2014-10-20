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

void circle_random_init(struct shape_data *data) {
  data->area=circle_area;
  data->circumference=circle_circumference;
  data->printer=circle_printer;
  data->a = random_double();
  data->b = 0;
  data->c = 0;
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

void square_random_init(struct shape_data *data) {
  data->area=square_area;
  data->circumference=square_circumference;
  data->printer=square_printer;
  data->a = random_double();
  data->b = 0;
  data->c = 0;
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

void triangle_random_init(struct shape_data *data) {
  data->area=triangle_area;
  data->circumference=triangle_circumference;
  data->printer=triangle_printer;
  double u = random_double();
  double v = random_double();
  double w = random_double();
  data->a = u+v;
  data->b = v+w;
  data->c = u+w;
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
    if (strlen(arg) != 1) {
      usage(argv[0], "strlen of each argument must be 1");
    }
    char c = arg[0];
    switch (c) {
    case 'C':
      circle_random_init(&(array[i]));
      break;
    case 'S':
      square_random_init(&(array[i]));
      break;
    case 'T':
      triangle_random_init(&(array[i]));
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
