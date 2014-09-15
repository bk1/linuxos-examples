#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>

struct array_list {
  size_t size;
  size_t capacity;
  size_t member_size;
  void *data;
};

struct array_list create_list(size_t size, size_t capacity, size_t member_size);

int change_list_capacity(struct array_list list, size_t new_capacity);

int change_list_size(struct array_list list, size_t new_size);

int get_list_size(struct array_list list);

int get_list_capacity(struct array_list list);

void *get_from_list(struct array_list list, size_t index);

int set_in_list(struct array_list list, size_t index, void *entry);

int insert_in_list(struct array_list list, size_t index, void *entry);

int remove_from_list(struct array_list list, size_t index);

void *car(struct array_list list);

struct array_list copy(struct array_list list);

struct array_list copy_part(struct array_list list, size_t start, size_t size, size_t capacity);

int delete_list(struct array_list list);

#endif
