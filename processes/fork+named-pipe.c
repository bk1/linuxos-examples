/* (C) IT Sky Consulting GmbH 2014
 * http://www.it-sky-consulting.com/
 * Author: Karl Brodowsky
 * Date: 2014-02-27
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void usage(const char *argv0, const char *msg) {
  if (msg != NULL && strlen(msg) > 0) {
    printf("%s\n\n", msg);
  }
  printf("Usage\n\n");
  printf("%s pipe\n\n", argv0);
  printf("communicate from parent to child via pipe\n");
  exit(1);
}

void child_operations(char *pipe) {
  printf("starting child operations\n");
  fflush(stdout);
  FILE *input = fopen(pipe, "r");
  while (! feof(input)) {
    char buf[1025];
    int nbytes;
    nbytes = fread(buf, sizeof(char), 1024, input);
    buf[nbytes] = '\000';
    printf("found %d bytes: \"%s\"\n", nbytes, buf);
  }
  fclose(input);
  printf("done child operations\n");
  fflush(stdout);
}

void parent_operations(char *pipe) {
  printf("waiting for child to get ready\n");
  fflush(stdout);
  sleep(1);
  printf("starting parent operations\n");
  fflush(stdout);
  FILE *output = fopen(pipe, "w");
  for (int i = 0; i < 256; i++) {
    fprintf(output, "%4d^2=%6d\n", i, i*i);
    fflush(output);
    usleep(50);
  }
  fclose(output);
  printf("done parent operations\n");
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    usage(argv[0], "wrong number of arguments");
  }
  
  pid_t child_pid = fork();
  if (child_pid < 0) {
    printf("could not fork\n");
    exit(1);
  }
  if (child_pid == 0) {
    // in child
    child_operations(argv[1]);
  } else {
    // in parent
    printf("child_pid=%d\n", child_pid);
    parent_operations(argv[1]);
  }
  exit(0);
}
