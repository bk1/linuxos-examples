#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  for (int i = 0; i <= 20; i++) {
    if (fork() == 0) {
      char label[5];
      sprintf(label, "ID%02d", i);
      nice(i);
      char *args[] = { "./simpson", "0", "6.28", "1000000000", label };
      execv("./simpson", args);
    }
  }
  printf("forked all\n");
  sleep(30);
  printf("done all\n");
  exit(0);
}

