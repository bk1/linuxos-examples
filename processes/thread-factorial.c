/* (C) IT Sky Consulting GmbH 2014
 * http://www.it-sky-consulting.com/
 * Author: Karl Brodowsky
 * Date: 2014-02-27
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
 */



#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

struct factorial_data {
  unsigned int  n;
  unsigned long result;
};

/** ptr is factorial_data, result is space for storing result, n is used for providing input parameter */
void *factorial_run(void *ptr) {
  struct factorial_data *data = (struct factorial_data *) ptr;
  data->result = 1L;
  for (int i = 1; i <= data-> n; i++) {
    data->result *= i;
  }
  return (void *) &(data->result);
}

void usage(const char *argv0, const char *msg) {
  if (msg != NULL && strlen(msg) > 0) {
    printf("%s\n\n", msg);
  }
  printf("Usage\n\n");
  printf("%s n\n\tcalculates factorial of n assynchronously\n", argv0);
  exit(1);
}

int main(int argc, char *argv[]) {

  if (argc >= 2 && strcmp(argv[1], "--help") == 0 || argc != 2) {
    usage(argv[0], "");
  }

  unsigned int n = atoi(argv[1]);
  struct factorial_data data;
  data.n = n;

  pthread_t thread1;
  int retcode = pthread_create(&thread1, NULL, factorial_run, &data);
  if (retcode < 0) {
    printf("Error creating thread retcode=%d errno=%d\n", retcode, errno);
    exit(1);
  }
  long *retval_ptr;
  pthread_join(thread1, &retval_ptr);
  long result = *retval_ptr;
  printf("done %u! = %lu\n", n, result);
  exit(0);
}
