/* (C) IT Sky Consulting GmbH 2014
 * http://www.it-sky-consulting.com/
 * Author: Karl Brodowsky
 * Date: 2014-09-09
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
 */

/* implements tests for array-list */

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <stdlib.h>

#include "array-list.h"

void fprint_long_element(FILE *output, void *long_element, size_t member_size) {
  if (member_size != sizeof(long)) {
    fprintf(output, "{$$ size mismatch: expected %zd found %zd}", (size_t) sizeof(long), (size_t) member_size);
    return;
  }
  long *long_ptr = (long *) long_element;
  fprintf(output, "%ld", *long_ptr);
}

void fprint_string_element(FILE *output, void *str_element, size_t member_size) {
  char *char_ptr = (char *) str_element;
  fprintf(output, "\"");
  for (int i = 0; i < member_size; i++) {
    char c = *(char_ptr++);
    if (c < 32) {
      fprintf(output, "^%c", 0x40 | c);
    } else if (c == 0x7f) {
      fprintf(output, "^?");
    } else if (c == '\"') {
      fprintf(output, "\\\"");
    } else if (c == '\\') {
      fprintf(output, "\\\\");
    } else {
      fprintf(output, "%c", c);
    }
  }
  fprintf(output, "\"");
}

void check_zero(void *ptr, size_t size) {
  size_t i;
  for (i = 0; i < size; i++) {
    CU_ASSERT_EQUAL(0, *((char *)(ptr++)));
  }
}

/* The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1() {
  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void) {
  return 0;
}

/* Simple test of creating and using an empty array-list
 */
void test_empty_list() {
  for (size_t cap = 1; cap <= 5; cap++) {
    struct array_list list;
    int rc = create_list(&list, 0, cap, 1);
    CU_ASSERT_EQUAL(rc, 0);
    size_t s = get_list_size(&list);
    CU_ASSERT_EQUAL(s, 0);
    size_t c = get_list_capacity(&list);
    CU_ASSERT_EQUAL(c, cap);
    printf("empty_list=");
    print_list(&list, stdout, fprint_long_element);
    printf("\n");
    delete_list(&list);
  }
}

void test_one_element_list() {
  for (size_t cap = 1; cap <= 5; cap++) {
    for (size_t msize = 1; msize <= 5; msize++){
      struct array_list list;
      int rc = create_list(&list, 1, cap, msize);
      CU_ASSERT_EQUAL(rc, 0);
      size_t s = get_list_size(&list);
      CU_ASSERT_EQUAL(s, 1);
      size_t c = get_list_capacity(&list);
      CU_ASSERT_EQUAL(c, cap);
      void *element = get_element_reference_from_list(&list, 0);
      check_zero(element, msize);
      delete_list(&list);
    }
  }
}

void test_one_element_long_list() {
  for (size_t cap = 1; cap <= 5; cap++) {
    size_t msize = sizeof(long);
    struct array_list list;
    int rc = create_list(&list, 1, cap, msize);
    CU_ASSERT_EQUAL(rc, 0);
    size_t s = get_list_size(&list);
    CU_ASSERT_EQUAL(s, 1);
    size_t c = get_list_capacity(&list);
    CU_ASSERT_EQUAL(c, cap);
    void *element = get_element_reference_from_list(&list, 0);
    check_zero(element, msize);
    for (long l = -5; l <= 5; l++) {
      set_in_list(&list, 0, &l);
      printf("l=%2ld: one_element_long_list=", l);
      print_list(&list, stdout, fprint_long_element);
      printf("\n");
    }
    delete_list(&list);
  }
}

void test_create_wrong_param() {
  int rc;
  struct array_list list;
  // size < 0
  rc = create_list(&list, -1, 1, 1);
  CU_ASSERT_EQUAL(rc, ILLEGAL_PARAMETER_VALUE);
  delete_list(&list);
  // capacity < size
  rc = create_list(&list, 2, 1, 1);
  CU_ASSERT_EQUAL(rc, ILLEGAL_PARAMETER_VALUE);
  delete_list(&list);
  // capacity = 0
  rc = create_list(&list, 0, 0, 1);
  CU_ASSERT_EQUAL(rc, ILLEGAL_PARAMETER_VALUE);
  delete_list(&list);
  // member_size = 0
  rc = create_list(&list, 1, 1, 0);
  CU_ASSERT_EQUAL(rc, ILLEGAL_PARAMETER_VALUE);
  delete_list(&list);
  // capacity too big
  rc = create_list(&list, 1, 100000, 1000000);
  CU_ASSERT_EQUAL(rc, ALLOCATE_FAILED);
  delete_list(&list);
  // capacity too big
  rc = create_list(&list, 1, 1000000, 1000000);
  CU_ASSERT_EQUAL(rc, ALLOCATE_FAILED);
  delete_list(&list);
  // capacity too big
  rc = create_list(&list, 1, 100000000L, 1000000000L);
  CU_ASSERT_EQUAL(rc, ALLOCATE_FAILED);
  delete_list(&list);
  // capacity too big
  rc = create_list(&list, 1, 10000000000L, 100000000000L);
  CU_ASSERT_EQUAL(rc, ILLEGAL_PARAMETER_VALUE);
  delete_list(&list);
}

void test_change_list_capacity() {
  int rc;
  int c;
  struct array_list list;

  // new capacity < size
  size_t size = 2;
  size_t msize = 2;
  rc = create_list(&list, size, 2, msize);
  CU_ASSERT_EQUAL(0, rc);
  for (int i = 0; i < size; i++) {
    void *element = get_element_reference_from_list(&list, i);
    check_zero(element, msize);
  }
  rc = change_list_capacity(&list, 1);
  CU_ASSERT_EQUAL(rc, ILLEGAL_PARAMETER_VALUE);
  delete_list(&list);

  // new capacity <= 0
  rc = create_list(&list, 0, 2, 2);
  CU_ASSERT_EQUAL(0, rc);
  rc = change_list_capacity(&list, 0);
  CU_ASSERT_EQUAL(rc, ILLEGAL_PARAMETER_VALUE);
  delete_list(&list);

  // new capacity bigger than old
  rc = create_list(&list, 0, 2, 2);
  CU_ASSERT_EQUAL(0, rc);
  rc = change_list_capacity(&list, 3);
  CU_ASSERT_EQUAL(rc, 0);
  c = get_list_capacity(&list);
  CU_ASSERT_EQUAL(c, 3);
  delete_list(&list);

  // new capacity smaller than old
  rc = create_list(&list, 0, 2, 2);
  CU_ASSERT_EQUAL(0, rc);
  rc = change_list_capacity(&list, 1);
  CU_ASSERT_EQUAL(rc, 0);
  c = get_list_capacity(&list);
  CU_ASSERT_EQUAL(c, 1);
  delete_list(&list);
}

void test_change_list_size() {
  int rc;
  int s;
  int c;
  struct array_list list;
  size_t msize = 2;

  // new size < 0 will be transformed into 0xfffffffffffff a big positive number not allocatable.
  rc = create_list(&list, 0, 2, msize);
  CU_ASSERT_EQUAL(0, rc);
  rc = change_list_size(&list, -1);
  CU_ASSERT_EQUAL(rc, ALLOCATE_FAILED);
  delete_list(&list);

  // new size bigger than old size and than old capacity
  rc = create_list(&list, 0, 2, msize);
  CU_ASSERT_EQUAL(0, rc);
  rc = change_list_size(&list, 3);
  CU_ASSERT_EQUAL(rc, 0);
  s = get_list_size(&list);
  CU_ASSERT_EQUAL(s, 3);
  c = get_list_capacity(&list);
  CU_ASSERT_EQUAL(c, 3);
  for (int i = 0; i < 3; i++) {
    void *element = get_element_reference_from_list(&list, i);
    check_zero(element, msize);
  }
  delete_list(&list);

  // new size bigger than old size and not bigger than old capacity
  rc = create_list(&list, 0, 4, msize);
  CU_ASSERT_EQUAL(0, rc);
  rc = change_list_size(&list, 3);
  CU_ASSERT_EQUAL(rc, 0);
  s = get_list_size(&list);
  CU_ASSERT_EQUAL(s, 3);
  c = get_list_capacity(&list);
  CU_ASSERT_EQUAL(c, 4);
  for (int i = 0; i < 3; i++) {
    void *element = get_element_reference_from_list(&list, i);
    check_zero(element, msize);
  }
  delete_list(&list);

  // new size smaller than old
  rc = create_list(&list, 2, 2, msize);
  CU_ASSERT_EQUAL(0, rc);
  for (int i = 0; i < 2; i++) {
    void *element = get_element_reference_from_list(&list, i);
    check_zero(element, msize);
  }
  rc = change_list_size(&list, 1);
  CU_ASSERT_EQUAL(rc, 0);
  void *element = get_element_reference_from_list(&list, 0);
  check_zero(element, msize);
  s = get_list_size(&list);
  CU_ASSERT_EQUAL(s, 1);
  c = get_list_capacity(&list);
  CU_ASSERT_EQUAL(c, 2);
  delete_list(&list);
}

void test_set_in_list_replace() {
  size_t cap;
  static char *bytes = "abcdefghijklmnopqrstuvwxyz";
  for (size_t size = 1;size < 5; size++) {
    cap = size;
    for (size_t msize = 1; msize <= 5; msize++) {
      struct array_list list;
      int rc = create_list(&list, size, cap, msize);
      CU_ASSERT_EQUAL(rc, 0);
      for (int i = 0; i < size; i++) {
        void *element = get_element_reference_from_list(&list, i);
        check_zero(element, msize);
      }
      for (int i = 0; i < size; i++) {
        rc = set_in_list(&list, i, (void *)(bytes + i));
        CU_ASSERT_EQUAL(rc, 0);
      }
      printf("s=%zd m=%zd l=", size, msize);
      print_list(&list, stdout, fprint_string_element);
      printf("\n");
      for (int i = 0; i < size; i++) {
        void *element = get_element_reference_from_list(&list, i);
        char *celement = (char *) element;
        for (int j = 0; j < msize; j++) {
          CU_ASSERT_EQUAL(celement[j], bytes[i+j]);
        }
        char ccelement[5];
        rc = copy_element_from_list(&ccelement, &list, i);
        CU_ASSERT_EQUAL(rc, 0);
        for (int j = 0; j < msize; j++) {
          CU_ASSERT_EQUAL(celement[j], bytes[i+j]);
        }
      }
      delete_list(&list);
    }
  }
}

void test_set_in_long_list_replace() {
  size_t cap = 1;
  for (size_t size = 1;size < 5; size++) {
    size_t msize = sizeof(long);
    struct array_list list;
    cap = size;
    int rc = create_list(&list, cap, size, msize);
    CU_ASSERT_EQUAL(rc, 0);
    for (int i = 0; i < size; i++) {
      void *element = get_element_reference_from_list(&list, i);
      check_zero(element, msize);
    }
    for (int i = 0; i < size; i++) {
      long l = i*i*i;
      rc = set_in_list(&list, i, &l);
      CU_ASSERT_EQUAL(rc, 0);
    }
    printf("s=%zd m=%zd l=", size, msize);
    print_list(&list, stdout, fprint_long_element);
    printf("\n");
    for (int i = 0; i < size; i++) {
      void *element = get_element_reference_from_list(&list, i);
      long *lelement = (long *) element;
      CU_ASSERT_EQUAL(*lelement, i*i*i);
      long ll;
      rc = copy_element_from_list(&ll, &list, i);
      CU_ASSERT_EQUAL(rc, 0);
      CU_ASSERT_EQUAL(ll, i*i*i);
    }      
    delete_list(&list);
  }
}

void test_set_in_list_extend() {
  static char *bytes = "abcdefghijklmnopqrstuvwxyz";
  for (size_t size = 1;size < 5; size++) {
    for (size_t msize = 1; msize <= 5; msize++) {
      struct array_list list;
      int rc = create_list(&list, 0, 1, msize);
      CU_ASSERT_EQUAL(rc, 0);
      int s = get_list_size(&list);
      CU_ASSERT_EQUAL(s, 0);
      for (int i = size - 1; i >= 0; i--) {
        rc = set_in_list(&list, i, (void *)(bytes + i));
        CU_ASSERT_EQUAL(rc, 0);
        int s = get_list_size(&list);
        CU_ASSERT_EQUAL(s, size);
        for (int j = 0; j < i; j++) {
          void *element = get_element_reference_from_list(&list, j);
          check_zero(element, msize);
        }
      }
      printf("s=%zd m=%zd l=", size, msize);
      print_list(&list, stdout, fprint_string_element);
      printf("\n");
      for (int i = 0; i < size; i++) {
        void *element = get_element_reference_from_list(&list, i);
        char *celement = (char *) element;
        for (int j = 0; j < msize; j++) {
          CU_ASSERT_EQUAL(celement[j], bytes[i+j]);
        }
        char ccelement[5];
        rc = copy_element_from_list(&ccelement, &list, i);
        CU_ASSERT_EQUAL(rc, 0);
        for (int j = 0; j < msize; j++) {
          CU_ASSERT_EQUAL(celement[j], bytes[i+j]);
        }
      }
      delete_list(&list);
    }
  }
}

void test_set_in_long_list_extend() {
  for (size_t size = 1;size < 5; size++) {
    size_t msize = sizeof(long);
    struct array_list list;
    int rc = create_list(&list, 0, 1, msize);
    CU_ASSERT_EQUAL(rc, 0);
    int s = get_list_size(&list);
    CU_ASSERT_EQUAL(s, 0);
    for (int i = size-1; i >= 0; i--) {
      long l = i*i*i;
      rc = set_in_list(&list, i, &l);
      CU_ASSERT_EQUAL(rc, 0);
      for (int j = 0; j < i; j++) {
      void *element = get_element_reference_from_list(&list, j);
      check_zero(element, msize);
    }
    }
    printf("s=%zd m=%zd l=", size, msize);
    print_list(&list, stdout, fprint_long_element);
    printf("\n");
    for (int i = 0; i < size; i++) {
      void *element = get_element_reference_from_list(&list, i);
      long *lelement = (long *) element;
      CU_ASSERT_EQUAL(*lelement, i*i*i);
      long ll;
      rc = copy_element_from_list(&ll, &list, i);
      CU_ASSERT_EQUAL(rc, 0);
      CU_ASSERT_EQUAL(ll, i*i*i);
    }      
    delete_list(&list);
  }
}

void test_insert_in_list_extend() {
  static char *bytes = "abcdefghijklmnopqrstuvwxyz";
  for (size_t size = 1;size < 5; size++) {
    for (size_t msize = 1; msize <= 5; msize++) {
      struct array_list list;
      int rc = create_list(&list, 0, 1, msize);
      CU_ASSERT_EQUAL(rc, 0);
      int s = get_list_size(&list);
      CU_ASSERT_EQUAL(s, 0);
      for (int i = 0; i < size; i++) {
        rc = insert_in_list(&list, i, (void *)(bytes + i));
        CU_ASSERT_EQUAL(rc, 0);
        int s = get_list_size(&list);
        CU_ASSERT_EQUAL(s, i+1);
        for (int j = 0; j <= i; j++) {
          void *element = get_element_reference_from_list(&list, j);
          char *celement = (char *) element;
          for (int k = 0; k < msize; k++) {
            CU_ASSERT_EQUAL(celement[k], bytes[j+k]);
          }
        }
      }
      printf("s=%zd m=%zd l=", size, msize);
      print_list(&list, stdout, fprint_string_element);
      printf("\n");
      for (int i = 0; i < size; i++) {
        void *element = get_element_reference_from_list(&list, i);
        char *celement = (char *) element;
        for (int j = 0; j < msize; j++) {
          CU_ASSERT_EQUAL(celement[j], bytes[i+j]);
        }
        char ccelement[5];
        rc = copy_element_from_list(&ccelement, &list, i);
        CU_ASSERT_EQUAL(rc, 0);
        for (int j = 0; j < msize; j++) {
          CU_ASSERT_EQUAL(celement[j], bytes[i+j]);
        }
      }
      delete_list(&list);
    }
  }
}

void test_insert_in_long_list_extend() {
  for (size_t size = 1;size < 5; size++) {
    size_t msize = sizeof(long);
    struct array_list list;
    int rc = create_list(&list, 0, 1, msize);
    CU_ASSERT_EQUAL(rc, 0);
    int s = get_list_size(&list);
    CU_ASSERT_EQUAL(s, 0);
    for (int i = 0; i < size; i++) {
      long l = i*i*i;
      rc = insert_in_list(&list, i, &l);
      CU_ASSERT_EQUAL(rc, 0);
      int s = get_list_size(&list);
      CU_ASSERT_EQUAL(s, i+1);
      for (int j = 0; j <= i; j++) {
        void *element = get_element_reference_from_list(&list, j);
        long *lelement = (long *) element;
        CU_ASSERT_EQUAL(*lelement, j*j*j);
      }
    }
    printf("s=%zd m=%zd l=", size, msize);
    print_list(&list, stdout, fprint_long_element);
    printf("\n");
    for (int i = 0; i < size; i++) {
      void *element = get_element_reference_from_list(&list, i);
      long *lelement = (long *) element;
      CU_ASSERT_EQUAL(*lelement, i*i*i);
      long ll;
      rc = copy_element_from_list(&ll, &list, i);
      CU_ASSERT_EQUAL(rc, 0);
      CU_ASSERT_EQUAL(ll, i*i*i);
    }      
    delete_list(&list);
  }
}

void test_insert_in_long_list_shift() {
  for (size_t size = 1;size < 5; size++) {
    size_t msize = sizeof(long);
    struct array_list list;
    int rc = create_list(&list, 0, 1, msize);
    CU_ASSERT_EQUAL(rc, 0);
    int s = get_list_size(&list);
    CU_ASSERT_EQUAL(s, 0);
    for (int i = 0; i < size; i++) {
      long l = i*i*i;
      rc = insert_in_list(&list, 0, &l);
      CU_ASSERT_EQUAL(rc, 0);
      int s = get_list_size(&list);
      CU_ASSERT_EQUAL(s, i+1);
      for (int j = 0; j <= i; j++) {
        void *element = get_element_reference_from_list(&list, j);
        long *lelement = (long *) element;
        int ii = i - j;
        long ll = ii*ii*ii;
        CU_ASSERT_EQUAL(*lelement, ll);
      }
    }
    printf("s=%zd m=%zd l=", size, msize);
    print_list(&list, stdout, fprint_long_element);
    printf("\n");
    for (int i = 0; i < size; i++) {
      void *element = get_element_reference_from_list(&list, i);
      long *lelement = (long *) element;
      int ii = size - 1 - i;
      long lx = ii*ii*ii;
      CU_ASSERT_EQUAL(*lelement, lx);
      long ll;
      rc = copy_element_from_list(&ll, &list, i);
      CU_ASSERT_EQUAL(rc, 0);
      CU_ASSERT_EQUAL(ll, lx);
    }      
    delete_list(&list);
  }
}

void test_insert_in_long_list_middle() {
  size_t size = 2;
  size_t msize = sizeof(long);
  size_t cap = size + 1;
  struct array_list list;
  int rc = create_list(&list, size, cap, msize);
  CU_ASSERT_EQUAL(rc, 0);
  int s = get_list_size(&list);
  CU_ASSERT_EQUAL(s, size);
  for (int i = 0; i < size; i++) {
    long ii = i+1;
    long l = ii*ii*ii;
    rc = set_in_list(&list, i, &l);
    CU_ASSERT_EQUAL(rc, 0);
    int s = get_list_size(&list);
    CU_ASSERT_EQUAL(s, size);
  }
  long ll = -1;
  insert_in_list(&list, 1, &ll);
  s = get_list_size(&list);
  CU_ASSERT_EQUAL(s, size+1);

  void *element;
  long *lelement;
  long ii = 1;
  ll = ii*ii*ii;
  element = get_element_reference_from_list(&list, 0);
  lelement = (long *) element;
  CU_ASSERT_EQUAL(*lelement, ll);

  ll = -1;
  element = get_element_reference_from_list(&list, 1);
  lelement = (long *) element;
  CU_ASSERT_EQUAL(*lelement, ll);

  ii = 2;
  ll = ii*ii*ii;
  element = get_element_reference_from_list(&list, 2);
  lelement = (long *) element;
  CU_ASSERT_EQUAL(*lelement, ll);
  delete_list(&list);
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry()) {
    return CU_get_error();
  }

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "test of zero element list", test_empty_list))
      || (NULL == CU_add_test(pSuite, "test of one element list", test_one_element_list))
      || (NULL == CU_add_test(pSuite, "test of one element long list", test_one_element_long_list))
      || (NULL == CU_add_test(pSuite, "test of wrong parameters for creting list", test_create_wrong_param))
      || (NULL == CU_add_test(pSuite, "test change of list capacity", test_change_list_capacity))
      || (NULL == CU_add_test(pSuite, "test change of list size", test_change_list_size))
      || (NULL == CU_add_test(pSuite, "set element in list", test_set_in_list_replace))
      || (NULL == CU_add_test(pSuite, "set element in list", test_set_in_long_list_replace))
      || (NULL == CU_add_test(pSuite, "set element in list", test_set_in_list_extend))
      || (NULL == CU_add_test(pSuite, "set element in list", test_set_in_long_list_extend))
      || (NULL == CU_add_test(pSuite, "insert element in list", test_insert_in_list_extend))
      || (NULL == CU_add_test(pSuite, "insert element in list", test_insert_in_long_list_extend))
      || (NULL == CU_add_test(pSuite, "insert element in list", test_insert_in_long_list_shift))
      || (NULL == CU_add_test(pSuite, "insert element in list", test_insert_in_long_list_middle))


      /* || (NULL == CU_add_test(pSuite, "test of sorts on one-element sets", test_sort_one)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on ascending two-element sets", test_sort_two_asc)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on descending two-element sets", test_sort_two_desc)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on two-element sets with both elements the same", test_sort_two_same)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on all kinds of positive three-element sets", test_sort_three)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on all kinds of negative three-element sets", test_sort_neg_three)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on all lengths from 0 to 100 of an ascending set", test_ascending_n)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on all lengths from 0 to 100 of an descending set", test_descending_n)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on all lengths from 0 to 100 of an negative set", test_negative_n)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on all lengths from 0 to 100 of an oscillating set", test_oscillating_n)) */
      /* || (NULL == CU_add_test(pSuite, "test of sorts on all lengths from 0 to 100 of an random set", test_random_n)) */
      ) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run all tests using the CUnit Basic interface */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  CU_basic_run_tests();
  CU_cleanup_registry();
  return CU_get_error();
}
