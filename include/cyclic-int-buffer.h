#ifndef CYCLIC_INT_BUFFER_H
#define CYCLIC_INT_BUFFER_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define ILLEGAL_PARAMETER_VALUE (-1)
#define ALLOCATE_FAILED (-2)
#define COPY_FAILED (-3)
#define ZERO_INIT_FAILED (-4)
#define INDEX_OUT_OF_RANGE (-5)
#define LIST_ALREADY_EMPTY (-6)
#define UNKNOWN_ERROR (-7)
#define BUFFER_IS_EMPTY (-8)

/* struct to hold the whole cyclic int buffer
 * size is the number of elements actually in the cyclic_buffer
 * capacity is the number of elements for which the cyclic_buffer is prepared
 * internal_capacity is one more, which allows handling of size more easily
 * read_idx is the next member position to read from
 * write_idx is the next member position to write to
 * data is the memory area where the elements are stored
 */
struct cyclic_int_buffer {
  size_t internal_capacity;
  size_t read_idx;
  size_t write_idx;
  int is_empty;
  int is_full;
  pthread_mutex_t read_mutex;
  pthread_mutex_t write_mutex;
  pthread_mutex_t empty_read_mutex;
  pthread_mutex_t full_write_mutex;
  int *data;
};

/*
 * creates a cyclic int buffer of the given capacity
 * required:
 * capacity > 0
 * return:
 *   0 on sucess
 *   ILLEGAL_PARAMETER_VALUE if parameter value is not correct
 *   ALLOCATE_FAILED if allocation of memory failed
 */
int create_cyclic_int_buffer(struct cyclic_int_buffer *cyclic_buffer, size_t capacity);

/*
 * gets the size of the cyclic_buffer
 * return:
 *   size of cyclic_buffer
 */
size_t get_cyclic_buffer_size(struct cyclic_int_buffer *cyclic_buffer);

/*
 * gets the capaity of cyclic_buffer
 * return:
 *   capaity of cyclic_buffer
 */
size_t get_cyclic_buffer_capacity(struct cyclic_int_buffer *cyclic_buffer);

/*
 * gets an entry from the cyclic buffer
 * return:
 *   0 when ok
 *   <0 when error
 *  actual result is stored in *result
 */
int get_element_from_cyclic_buffer(struct cyclic_int_buffer *cyclic_buffer, size_t index, int *result);

int put(struct cyclic_int_buffer *cyclic_buffer, int value);

int get(struct cyclic_int_buffer *cyclic_buffer);

/*
 * free memory allocated
 * return 0 if successful
 * return UNKNOWN_ERROR if free failed
 */
int delete_cyclic_buffer(struct cyclic_int_buffer *cyclic_buffer);

int print_cyclic_buffer(struct cyclic_int_buffer *cyclic_buffer, FILE *output);

#endif
