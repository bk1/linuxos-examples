#include <array-list.h>

#include <stdlib.h>
#include <string.h>

void zero_data(struct array_list list, size_t begin, size_t beyond_end) {
  memset((void *) (list.data + begin*list.member_size), 0, (beyond_end - begin) * list.member_size);
}


struct array_list create_list(size_t size, size_t capacity, size_t member_size) {
  if (size < 0) {
    size = 0;
  }
  if (capacity < size) {
    capacity = size;
  }
  if (capacity <= 0) {
    capacity = 1;
  }
  if (member_size <= 0) {
    member_size = 1;
  }
  struct array_list result = { .size = size,
                               .capacity = capacity,
                               .member_size = member_size,
                               .data = malloc(capacity * member_size) };
  zero_data(result, 0, size);
  return result;
}

int change_list_capacity(struct array_list list, size_t new_capacity) {
  if (new_capacity < list.size) {
    new_capacity = list.size;
  }
  if (new_capacity != list.capacity) {
    void *rr = realloc(list.data, new_capacity * list.member_size);
    if (rr == (void *)NULL) {
      return -1;
    }
    list.capacity = new_capacity;
  }
  return 0;
}

int change_list_size(struct array_list list, size_t new_size) {
  if (new_size > list.capacity) {
    change_list_capacity(list, new_size);
  }
  if (new_size > list.size) {
    zero_data(list, list.size, new_size);
  }
  list.size = new_size;
  return 0;
}

int get_list_size(struct array_list list) {
  return list.size;
}

int get_list_capacity(struct array_list list) {
  return list.capacity;
}

void *get_from_list(struct array_list list, size_t index) {
  if (index < 0 || index > list.size) {
    return (void *) NULL;
  } else {
    return list.data + list.member_size * index;
  }
}

int set_in_list(struct array_list list, size_t index, void *entry) {
  if (index >= list.size) {
    change_list_size(list, index + 1);
  }
  memcpy(list.data + list.member_size * index, entry, list.member_size);
  return 0;
}


int insert_in_list(struct array_list list, size_t index, void *entry) {
  if (index >= list.size) {
    return set_in_list(list, index, entry);
  }

  change_list_size(list, list.size + 1);
  void * rr = memmove(list.data + list.member_size * (index + 1), list.data + list.member_size * index, (list.size - index - 1) * list.member_size);
  if (rr == (void *) NULL) {
    return -1;
  }
  return 0;
}

int remove_from_list(struct array_list list, size_t index) {
  if (index < list.size) {
    void *rr = memmove(list.data + list.member_size * index, list.data + list.member_size * (index + 1), (list.size - index - 1) * list.member_size);
    if (rr == (void *) NULL) {
      return -1;
    }
  }
  change_list_size(list, list.size - 1);
  return 0;
}

void *car(struct array_list list) {
  return list.data;
}

struct array_list copy(struct array_list list) {
  struct array_list result = { .size = list.size,
                               .capacity = list.capacity,
                               .member_size = list.member_size,
                               .data = malloc(list.capacity * list.member_size) };
  memcpy(result.data, list.data, list.size * list.member_size);
  return result;
}

struct array_list copy_part(struct array_list list, size_t start, size_t size, size_t capacity) {
  if (size < 0) {
    size = 0;
  }
  if (start < 0) {
    start = 0;
  }
  if (start >= list.size) {
    size = 0;
  }
  if (start + size > list.size) {
    size = list.size - start;
  }
  if (capacity < size) {
    capacity = size;
  }
  struct array_list result = { .size = size,
                               .capacity = capacity,
                               .member_size = list.member_size,
                               .data = malloc(capacity * list.member_size) };
  memcpy(result.data, list.data + start * list.member_size, size * list.member_size);
  return result;
}

int delete_list(struct array_list list) {
  free(list.data);
  list.data = (void *) NULL;
  list.size = 0;
  list.capacity = 0;
  return 0;
}

