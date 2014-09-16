#include <array-list.h>

#include <stdlib.h>
#include <string.h>

/* internal use only */
void zero_data(struct array_list *list, size_t begin, size_t beyond_end) {
  size_t ms = list->member_size;
  memset((void *) (list->data + begin * ms), 0, (beyond_end - begin) * ms);
}

int create_list(struct array_list *list, size_t size, size_t capacity, size_t member_size) {
  if (size < 0) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  if (capacity < size) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  if (capacity <= 0) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  if (member_size <= 0) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  if (list == NULL) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  list->size = size;
  list->capacity = capacity;
  list->member_size = member_size;
  size_t mem_size = capacity * member_size;
  if (mem_size <= 0 || mem_size / capacity != member_size || mem_size % capacity != 0 || mem_size / member_size != capacity || mem_size % member_size != 0) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  list->data = malloc(mem_size);
  if (list->data == NULL) {
    return ALLOCATE_FAILED;
  }
  zero_data(list, 0, size);
  return 0;
}

int change_list_capacity(struct array_list *list, size_t new_capacity) {
  if (new_capacity <= 0 || new_capacity < list->size) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  if (new_capacity != list->capacity) {
    void *rr = realloc(list->data, new_capacity * list->member_size);
    if (rr == (void *)NULL) {
      return ALLOCATE_FAILED;
    }
    list->capacity = new_capacity;
  }
  return 0;
}

int change_list_size(struct array_list *list, size_t new_size) {
  if (new_size < 0) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  if (new_size > list->capacity) {
    int rc = change_list_capacity(list, new_size);
    if (rc < 0) {
      return rc;
    }
  }
  if (new_size > list->size) {
    zero_data(list, list->size, new_size);
  }
  list->size = new_size;
  return 0;
}

int get_list_size(struct array_list *list) {
  return list->size;
}

int get_list_capacity(struct array_list *list) {
  return list->capacity;
}

void *get_element_reference_from_list(struct array_list *list, size_t index) {
  if (index < 0 || index >= list->size) {
    return (void *) NULL;
  } else {
    return list->data + list->member_size * index;
  }
}

int copy_element_from_list(void *destination, struct array_list *list, size_t index) {
  void *element_ref = get_element_reference_from_list(list, index);
  if (element_ref == NULL) {
    return INDEX_OUT_OF_RANGE;
  }
  memcpy(destination, element_ref, list->member_size);
  return 0;
}

int set_in_list(struct array_list *list, size_t index, void *entry) {
  if (index < 0) {
    return INDEX_OUT_OF_RANGE;
  }
  if (index >= list->size) {
    int rc = change_list_size(list, index + 1);
    if (rc < 0) {
      return rc;
    }
  }
  memcpy(list->data + list->member_size * index, entry, list->member_size);
  return 0;
}


int insert_in_list(struct array_list *list, size_t index, void *entry) {
  if (index < 0) {
    return INDEX_OUT_OF_RANGE;
  }
  if (index < list->size) {
    int rc = change_list_size(list, list->size + 1);
    if (rc < 0) {
      return rc;
    }
    memmove(list->data + list->member_size * (index + 1), list->data + list->member_size * index, (list->size - index - 1) * list->member_size);
  }
  return set_in_list(list, index, entry);
}

void *first(struct array_list *list) {
  if (list->size == 0) {
    return NULL;
  } else {
    return list->data;
  }
}

void *last(struct array_list *list) {
  if (list->size == 0) {
    return NULL;
  } else {
    return list->data + (list->size - 1) * list->member_size;
  }
}

int remove_last_from_list(struct array_list *list) {
  if (list->size == 0) {
    return LIST_ALREADY_EMPTY;
  }
  return change_list_size(list, list->size - 1);
}  

int remove_from_list(struct array_list *list, size_t index) {
  if (list->size == 0) {
    return LIST_ALREADY_EMPTY;
  }
  if (index < 0 || index >= list->size) {
    return INDEX_OUT_OF_RANGE;
  }
  memmove(list->data + list->member_size * index, list->data + list->member_size * (index + 1), (list->size - index - 1) * list->member_size);
  return change_list_size(list, list->size - 1);
}

int copy(struct array_list *dest, struct array_list *source) {
  dest->size = source->size;
  dest->capacity = source->capacity;
  dest->member_size = source->member_size;
  size_t mem_size = source->capacity * source->member_size;
  if (mem_size <= 0) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  dest->data = malloc(mem_size);
  if (dest->data == NULL) {
    return ALLOCATE_FAILED;
  }
  memcpy(dest->data, source->data, source->size * source->member_size);
  return 0;
}

int copy_part(struct array_list *dest, struct array_list *src, size_t start, size_t size, size_t capacity) {
  if (size < 0) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  if (start < 0) {
    return INDEX_OUT_OF_RANGE;
  }
  if (start >= src->size) {
    return INDEX_OUT_OF_RANGE;
  }
  if (start + size > src->size) {
    return INDEX_OUT_OF_RANGE;
  }
  if (capacity <= 0 || capacity < size) {
    return ILLEGAL_PARAMETER_VALUE;
  }
  dest->size = size;
  dest->capacity = capacity;
  dest->member_size = src->member_size;
  dest->data = malloc(capacity * src->member_size);
  if (dest->data == NULL) {
    return ALLOCATE_FAILED;
  }
  memcpy(dest->data, src->data + start * src->member_size, size * src->member_size);
  return 0;
}

int delete_list(struct array_list *list) {
  free(list->data);
  list->data = (void *) NULL;
  list->size = 0;
  list->capacity = 0;
  return 0;
}

