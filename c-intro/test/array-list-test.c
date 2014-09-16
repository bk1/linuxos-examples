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
  for (int cap = 1; cap <= 5; cap++) {
    struct array_list list;
    int rc = create_list(&list, 0, cap, 1);
    CU_ASSERT_EQUAL(rc, 0);
    int s = get_list_size(&list);
    CU_ASSERT_EQUAL(s, 0);
    int c = get_list_capacity(&list);
    CU_ASSERT_EQUAL(c, cap);
    delete_list(&list);
  }
}

void test_one_element_list() {
  for (int cap = 1; cap <= 5; cap++) {
    for (int msize = 1; msize <= 5; msize++){
      struct array_list list;
      int rc = create_list(&list, 1, cap, msize);
      CU_ASSERT_EQUAL(rc, 0);
      int s = get_list_size(&list);
      CU_ASSERT_EQUAL(s, 1);
      int c = get_list_capacity(&list);
      CU_ASSERT_EQUAL(c, cap);
      void *element = get_element_reference_from_list(&list, 0);
      check_zero(element, msize);
      delete_list(&list);
    }
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
  int size = 2;
  int msize = 2;
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
  int msize = 2;

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

void test_set_int_list_replace() {
  int cap = 1;
  for (int size = 1;size < 5; size++) {
    for (int msize = 1; msize <= 5; msize++){
      struct array_list list;
      int rc = create_list(&list, size, cap, msize);
      CU_ASSERT_EQUAL(rc, 0);
      for (int i = 0; i < size; i++) {
        void *element = get_element_reference_from_list(&list, i);
        check_zero(element, msize);
      }
      // TODO
      delete_list(&list);
    }
  }
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
      || (NULL == CU_add_test(pSuite, "test of wrong parameters for creting list", test_create_wrong_param))
      || (NULL == CU_add_test(pSuite, "test change of list capacity", test_change_list_capacity))
      || (NULL == CU_add_test(pSuite, "test change of list size", test_change_list_size))

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
