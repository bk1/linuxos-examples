/* (C) IT Sky Consulting GmbH 2014
 * http://www.it-sky-consulting.com/
 * Author: Karl Brodowsky
 * Date: 2014-09-09
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
 */

/* implements a test-run for cyclic-int-buffer */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "cyclic-int-buffer.h"

struct arg_struct {
  int thread_number;
  int start_val;
  int count;
  int delay_limit;
  struct cyclic_int_buffer *cyclic_buffer;
};

unsigned int myrand(unsigned int limit) {
  unsigned int ui = rand();
  return ui % limit;
}

void *get_many(void *arg) {
  struct arg_struct *arg_s = (struct arg_struct *) arg;
  printf("started thread %d\n", arg_s->thread_number);
  for (int i = 0; i < arg_s->count; i++) {
    time_t t0 = time(NULL);
    int x = get(arg_s->cyclic_buffer);
    size_t s = get_cyclic_buffer_size(arg_s->cyclic_buffer);
    time_t t1 = time(NULL);
    printf("GET %4d: x=%7d s=%4zd t=%3d\n", arg_s->thread_number, x, s, (int) (t1-t0));
    sleep(myrand(arg_s->delay_limit));
  }
  printf("finishing thread %d\n", arg_s->thread_number);
  return NULL;
}

void *put_many(void *arg) {
  struct arg_struct *arg_s = (struct arg_struct *) arg;
  printf("started thread %d\n", arg_s->thread_number);
  for (int i = 0; i < arg_s->count; i++) {
    int x = arg_s->start_val + myrand(1000);
    time_t t0 = time(NULL);
    put(arg_s->cyclic_buffer, x);
    size_t s = get_cyclic_buffer_size(arg_s->cyclic_buffer);
    time_t t1 = time(NULL);
    printf("PUT %4d: x=%7d s=%4zd t=%3d\n", arg_s->thread_number, x, s, (int) (t1-t0));
    sleep(myrand(arg_s->delay_limit));
  }
  printf("finishing thread %d\n", arg_s->thread_number);
  return NULL;
}

int main(int argc, char *argv[]) {  
  int get_delay_limit = atoi(argv[1]);
  int put_delay_limit = atoi(argv[2]);
  pthread_t getter[10];
  pthread_t putter[10];
  struct arg_struct arg[20];
  struct cyclic_int_buffer cyclic_buffer;
  size_t cap = 100;
  create_cyclic_int_buffer(&cyclic_buffer, cap);
  for (int i = 0; i < 20; i++) {
    arg[i].thread_number = i;
    arg[i].start_val = 1000*i;
    arg[i].count = 200;
    arg[i].cyclic_buffer = &cyclic_buffer;
  }
  for (int i = 0; i < 10; i++) {
    arg[i].delay_limit = get_delay_limit;
    printf("starting thread %d\n", arg[i].thread_number);
    pthread_create(&getter[i], NULL, get_many, &arg[i]);
  }
  for (int i = 10; i < 20; i++) {
    arg[i].delay_limit = put_delay_limit;
    printf("starting thread %d\n", arg[i].thread_number);
    pthread_create(&putter[i-10], NULL, put_many, &arg[i]);
  }
  for (int i = 0; i < 10; i++) {
    pthread_join(getter[i], (void **) NULL);
    printf("finished thread %d\n", arg[i].thread_number);
    pthread_join(putter[i], (void **) NULL);
    printf("finished thread %d\n", arg[i+10].thread_number);
  }
}
