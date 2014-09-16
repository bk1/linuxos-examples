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
  if ((NULL == CU_add_test(pSuite, "test of sorts on empty sets", test_empty_list))
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
