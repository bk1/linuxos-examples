#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *output = NULL;
  if (argc != 1) {
    if (argc != 2 || strcmp(argv[1], "--help") == 0) {
      printf("Usage\n\n%s\nprints squares from 0 to 100 to stdout\n\n%s file\nprints squares to file\n", argv[0], argv[0]);
      exit(1);
    }
    output = argv[1];
  }
  FILE *out = NULL;
  if (output == NULL) {
    out = stdout;
  } else {
    out = fopen(output, "a");
  }
  int i;
  pid_t pid = getpid();
  for (i = 0; i <= 100; i++) {
    useconds_t duration = (useconds_t) (abs(rand() % 1000000));
    fprintf(out, "%4d^2=%6d %7ld (%4d)\n", i, i*i, (long) duration, (int) pid);
    fflush(out);
    usleep(duration);
  }
  fclose(out);
  exit(0);
}
