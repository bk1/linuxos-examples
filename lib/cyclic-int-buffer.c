#include <cyclic-int-buffer.h>

#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int create_cyclic_int_buffer(struct cyclic_int_buffer *cyclic_buffer, size_t capacity) {
  cyclic_buffer->internal_capacity = capacity + 1;
  cyclic_buffer->read_idx = 0;
  cyclic_buffer->write_idx = 0;
  cyclic_buffer->is_empty = 1;
  cyclic_buffer->is_full = 0;
  pthread_mutex_init(&(cyclic_buffer->read_mutex), NULL);
  pthread_mutex_init(&(cyclic_buffer->write_mutex), NULL);
  pthread_mutex_init(&(cyclic_buffer->empty_read_mutex), NULL);
  pthread_mutex_init(&(cyclic_buffer->full_write_mutex), NULL);
  pthread_mutex_lock(&(cyclic_buffer->empty_read_mutex));
  cyclic_buffer->data = (int *) malloc(cyclic_buffer->internal_capacity * sizeof(int));
  // TODO error handling
  return 0;
}

/*
 * gets the size of the cyclic_buffer
 * return:
 *   size of cyclic_buffer
 */
size_t get_cyclic_buffer_size(struct cyclic_int_buffer *cyclic_buffer) {
  int read_idx = cyclic_buffer->read_idx;
  int write_idx = cyclic_buffer->write_idx;
  int size = write_idx - read_idx;
  if (size < 0) {
    size += cyclic_buffer->internal_capacity;
  }
  return (size_t) size;
}

/*
 * gets the capacity of cyclic_buffer
 * return:
 *   capacity of cyclic_buffer
 */
size_t get_cyclic_buffer_capacity(struct cyclic_int_buffer *cyclic_buffer) {
  return cyclic_buffer->internal_capacity - 1;
}

/*
 * gets an entry from the cyclic buffer
 * return:
 *   0 when ok
 *   <0 when error
 *  actual result is stored in *result
 */
int get_element_from_cyclic_buffer(struct cyclic_int_buffer *cyclic_buffer, size_t index, int *result) {
  int retval = 0;
  *result = 0;
  pthread_mutex_lock(&(cyclic_buffer->read_mutex));
  int read_idx = cyclic_buffer->read_idx;
  int write_idx = cyclic_buffer->write_idx;
  if (read_idx == write_idx) {
    retval = BUFFER_IS_EMPTY;
  } else if (read_idx < write_idx) {
    if (read_idx <= index && index < write_idx) {
      *result = cyclic_buffer->data[index];
    } else {
      retval = INDEX_OUT_OF_RANGE;
    }
  } else { // read_idx > write_idx
    if (0 <= index && index < write_idx || read_idx <= index && index < cyclic_buffer->internal_capacity) {
      *result = cyclic_buffer->data[index];
    } else {
      retval = INDEX_OUT_OF_RANGE;
    }
  }
  pthread_mutex_unlock(&(cyclic_buffer->read_mutex));
  return retval;
}

int put(struct cyclic_int_buffer *cyclic_buffer, int value) {
  pthread_mutex_lock(&(cyclic_buffer->full_write_mutex));
  pthread_mutex_lock(&(cyclic_buffer->write_mutex));
  int write_idx = cyclic_buffer->write_idx;
  cyclic_buffer->data[write_idx] = value;
  write_idx++;
  write_idx %= cyclic_buffer->internal_capacity;
  cyclic_buffer->write_idx = write_idx;
  size_t size = get_cyclic_buffer_size(cyclic_buffer);
  cyclic_buffer->is_full = (size == cyclic_buffer->internal_capacity-1);
  if (! cyclic_buffer->is_full) {
    pthread_mutex_unlock(&(cyclic_buffer->full_write_mutex));
  }
  if (cyclic_buffer->is_empty) {
    cyclic_buffer->is_empty = 0;
    pthread_mutex_unlock(&(cyclic_buffer->empty_read_mutex));
  }
  pthread_mutex_unlock(&(cyclic_buffer->write_mutex));
  return 0;
}

int get(struct cyclic_int_buffer *cyclic_buffer) {
  pthread_mutex_lock(&(cyclic_buffer->empty_read_mutex));
  pthread_mutex_lock(&(cyclic_buffer->read_mutex));
  int read_idx = cyclic_buffer->read_idx;
  int result = cyclic_buffer->data[read_idx];
  read_idx++;
  read_idx %= cyclic_buffer->internal_capacity;
  cyclic_buffer->read_idx = read_idx;
  size_t size = get_cyclic_buffer_size(cyclic_buffer);
  cyclic_buffer->is_empty = (size == 0);
  if (! cyclic_buffer->is_empty) {
    pthread_mutex_unlock(&(cyclic_buffer->empty_read_mutex));
  }
  if (cyclic_buffer->is_full) {
    cyclic_buffer->is_full = 0;
    pthread_mutex_unlock(&(cyclic_buffer->full_write_mutex));
  }
  pthread_mutex_unlock(&(cyclic_buffer->read_mutex));
  return result;
}
  

/*
 * free memory allocated
 * return 0 if successful
 * return UNKNOWN_ERROR if free failed
 */
int delete_cyclic_buffer(struct cyclic_int_buffer *cyclic_buffer) {
  pthread_mutex_destroy(&(cyclic_buffer->read_mutex));
  pthread_mutex_destroy(&(cyclic_buffer->write_mutex));
  pthread_mutex_destroy(&(cyclic_buffer->empty_read_mutex));
  pthread_mutex_destroy(&(cyclic_buffer->full_write_mutex));
  free(cyclic_buffer->data);
  cyclic_buffer->data = NULL;
  return 0;
}
  

int print_cyclic_buffer(struct cyclic_int_buffer *cyclic_buffer, FILE *output) {
  int idx = cyclic_buffer->read_idx;
  int size = get_cyclic_buffer_size(cyclic_buffer);
  fprintf(output, "[");
  for (int i = 0; i < size; i++) {
    if (i > 0) {
      fprintf(output, ", ");
    }
    int val = cyclic_buffer->data[idx];
    idx++;
    idx %= cyclic_buffer->internal_capacity;
    fprintf(output, "%d=>%d", idx, val);
  }
  fprintf(output, "]\n");
}
