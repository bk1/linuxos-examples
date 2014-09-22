#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

#include <stdlib.h>
#include <stdio.h>

#define ILLEGAL_PARAMETER_VALUE (-1)
#define ALLOCATE_FAILED (-2)
#define COPY_FAILED (-3)
#define ZERO_INIT_FAILED (-4)
#define INDEX_OUT_OF_RANGE (-5)
#define LIST_ALREADY_EMPTY (-6)
#define UNKNOWN_ERROR (-7)

typedef void (*fprint_element_fun)(FILE *output, void *element, size_t member_size);

/* struct to hold the whole array list.
 * size is the number of elements actually in the list
 * capacity is the number of elements for which the list is prepared
 * member size is the size of each element
 * data is the memory area where the elements are stored
 */
struct array_list {
  size_t size;
  size_t capacity;
  size_t member_size;
  void *data;
};

/*
 * creates a list of the given capacity and size and member size
 * required:
 * size >= 0
 * capacity >= size
 * capacity > 0
 * member_size > 0
 * usually size=0 should be chosen.
 * if size > 0, the spaces for the entries are filled with 0-bytes.
 * fills list-struct with appropriate values.
 * return:
 *   0 on sucess
 *   ILLEGAL_PARAMETER_VALUE if parameter value is not correct
 *   ALLOCATE_FAILED if allocation of memory failed
 */
int create_list(struct array_list *list, size_t size, size_t capacity, size_t member_size);

/*
 * changes the capacity of list.  If necessary moves data to another location.
 * required:
 * new_capacity >= size
 * new_capacity > 0
 * return:
 *   0 on sucess
 *   ILLEGAL_PARAMETER_VALUE if parameter value is not correct
 *   ALLOCATE_FAILED if allocation of memory failed
 */
int change_list_capacity(struct array_list *list, size_t new_capacity);

/*
 * changes the size of list.  If necessary changes capacity.
 * required:
 * new_size >= 0
 * return:
 *   0 on sucess
 *   ILLEGAL_PARAMETER_VALUE if parameter value is not correct
 *   ALLOCATE_FAILED if allocation of memory failed
 *   ZERO_INIT_FAILED if filling of allocated space with 0 failed (should not happen)
 */
int change_list_size(struct array_list *list, size_t new_size);

/*
 * gets the size of the list
 * return:
 *   size of list
 */
int get_list_size(struct array_list *list);

/*
 * gets the capaity of list
 * return:
 *   capaity of list
 */
int get_list_capacity(struct array_list *list);

/*
 * gets a pointer referencing list entry
 * return:
 *   pointer to element in list if available
 *   NULL if not available
 */
void *get_element_reference_from_list(struct array_list *list, size_t index);

/*
 * copies an element from list to the given destination
 * return:
 *   0 on success
 *   INDEX_OUT_OF_RANGE if index is out of range
 *   COPY_FAILED if copying of data to destination failed
 */
int copy_element_from_list(void *destination, struct array_list *list, size_t index);

/*
 * copies element pointed to by entry into list at the given position.
 * changes size of list, if that position is not in the list.
 * stores 0-bytes if increasing the size leaves unused elements between new entry and existing entries.
 * returns:
 *   0 on sucess
 *   INDEX_OUT_OF_RANGE if index is < 0
 *   ILLEGAL_PARAMETER_VALUE if parameter value is not correct
 *   ALLOCATE_FAILED if allocation of memory failed
 *   COPY_FAILED if copying of data to destination failed
 *   ZERO_INIT_FAILED if filling of allocated space with 0 failed (should not happen)
 */
int set_in_list(struct array_list *list, size_t index, void *entry);

/*
 * inserts element pointed to by entry into list at the given position.
 * if elements exist at that position or above, they are moved up by one position and list size is increased by 1.
 * if no element exists at that position or above, changes size of list to make the newly inserted element the highest in list.
 * stores 0-bytes if increasing the size leaves unused elements between new entry and existing entries.
 * returns:
 *   0 on sucess
 *   INDEX_OUT_OF_RANGE if index is < 0
 *   ILLEGAL_PARAMETER_VALUE if parameter value is not correct
 *   ALLOCATE_FAILED if allocation of memory failed
 *   COPY_FAILED if copying of data to destination failed
 *   ZERO_INIT_FAILED if filling of allocated space with 0 failed (should not happen)
 */
int insert_in_list(struct array_list *list, size_t index, void *entry);

/*
 * appends element pointed to by entry to the end of the list.
 * list size is increased by 1.
 * returns:
 *   0 on sucess
 *   ILLEGAL_PARAMETER_VALUE if parameter value is not correct
 *   ALLOCATE_FAILED if allocation of memory failed
 *   COPY_FAILED if copying of data to destination failed
 *   ZERO_INIT_FAILED if filling of allocated space with 0 failed (should not happen)
 */
int append_to_list(struct array_list *list, void *entry);

/*
 * gets the first element of list (car)
 * NULL if list is empty
 */
void *first(struct array_list *list);

/*
 * gets the last element of list
 * NULL if list is empty
 */
void *last(struct array_list *list);

/*
 * removes the last element from list
 * return 0 if successful
 * ILLEGAL_PARAMETER_VALUE if list is already empty
 */
int remove_last_from_list(struct array_list *list);


/*
 * removes any element from list
 * if elements exist above the list, they are moved down one position
 * size decreases by 1
 * return 0 if successful
 * INDEX_OUT_OF_RANGE if index is < 0 or >= size
 * COPY_FAILED if moving of data failed 
 */
int remove_from_list(struct array_list *list, size_t index);

/*
 * copies list pointed to by source to dest
 * return 0 if successful
 * ALLOCATE_FAILED if allocation of data space failed
 * COPY_FAILED if copying of data failed
 */
int copy(struct array_list *dest, struct array_list *source);

/*
 * copies list pointed to by source to dest
 * return 0 if successful
 * INDEX_OUT_OF_RANGE if start or start + size-1 are not valid index values (>= 0,< size of source)
 * ILLEGAL_PARAMETER_VALUE if new capacity, new size are not correct
 * ALLOCATE_FAILED if allocation of data space failed
 * COPY_FAILED if copying of data failed
 */
int copy_part(struct array_list *dest, struct array_list *src, size_t start, size_t size, size_t capacity);

/*
 * free memory allocated
 * return 0 if successful
 * return UNKNOWN_ERROR if free failed
 */
int delete_list(struct array_list *list);

int print_list(struct array_list *list, FILE *output, fprint_element_fun fun);

#endif
