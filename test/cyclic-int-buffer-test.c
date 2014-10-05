/* (C) IT Sky Consulting GmbH 2014
 * http://www.it-sky-consulting.com/
 * Author: Karl Brodowsky
 * Date: 2014-09-09
 * License: GPL v2 (See https://de.wikipedia.org/wiki/GNU_General_Public_License )
 */

/* implements tests for cyclic-int-buffer */

#include <stdio.h>
#include <string.h>
#include <CUnit/Basic.h>
#include <stdlib.h>
#include <unistd.h>

#include "cyclic-int-buffer.h"

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

/* Simple test of creating and using an empty cyclic-int-buffer
 */
void test_empty_cyclic_buffer() {
  for (size_t cap = 1; cap <= 5; cap++) {
    struct cyclic_int_buffer cyclic_buffer;
    int rc = create_cyclic_int_buffer(&cyclic_buffer, cap);
    CU_ASSERT_EQUAL(rc, 0);
    size_t s = get_cyclic_buffer_size(&cyclic_buffer);
    CU_ASSERT_EQUAL(s, 0);
    size_t c = get_cyclic_buffer_capacity(&cyclic_buffer);
    CU_ASSERT_EQUAL(c, cap);
    printf("empty_cyclic_buffer=");
    print_cyclic_buffer(&cyclic_buffer, stdout);
    printf("\n");
    delete_cyclic_buffer(&cyclic_buffer);
  }
}

void test_one_element_cyclic_buffer() {
  for (size_t cap = 1; cap <= 5; cap++) {
    struct cyclic_int_buffer cyclic_buffer;
    int rc = create_cyclic_int_buffer(&cyclic_buffer, cap);
    CU_ASSERT_EQUAL(rc, 0);
    put(&cyclic_buffer, 22);
    size_t s = get_cyclic_buffer_size(&cyclic_buffer);
    CU_ASSERT_EQUAL(s, 1);
    int x = get(&cyclic_buffer);
    size_t c = get_cyclic_buffer_capacity(&cyclic_buffer);
    CU_ASSERT_EQUAL(c, cap);
    s = get_cyclic_buffer_size(&cyclic_buffer);
    CU_ASSERT_EQUAL(s, 0);
    CU_ASSERT_EQUAL(x, 22);
    delete_cyclic_buffer(&cyclic_buffer);
  }
}

void test_cyclic() {
  size_t cap = 5;
  struct cyclic_int_buffer cyclic_buffer;
  int rc = create_cyclic_int_buffer(&cyclic_buffer, cap);
  CU_ASSERT_EQUAL(rc, 0);
  for (int i = 0; i < 5; i++) {
    put(&cyclic_buffer, i);
    size_t s = get_cyclic_buffer_size(&cyclic_buffer);
    CU_ASSERT_EQUAL(s, i+1);
    printf("x=%d: ", i);
    print_cyclic_buffer(&cyclic_buffer, stdout);
  }
  int y = 0;
  int x = 5;
  for (int i = 0; i < 100; i++) {
    int yy = get(&cyclic_buffer);
    CU_ASSERT_EQUAL(yy, y);
    y++;
    put(&cyclic_buffer, x++);
    size_t s = get_cyclic_buffer_size(&cyclic_buffer);
    CU_ASSERT_EQUAL(s, 5);
    // printf("x=%d y=%d: ", x, yy);
    // print_cyclic_buffer(&cyclic_buffer, stdout);
  }
  for (int i = 0; i < 5; i++) {
    int yy = get(&cyclic_buffer);
    CU_ASSERT_EQUAL(yy, y);
    y++;
    printf("x=%d y=%d: ", x, yy);
    print_cyclic_buffer(&cyclic_buffer, stdout);
  }    

  size_t s = get_cyclic_buffer_size(&cyclic_buffer);
  CU_ASSERT_EQUAL(s, 0);
  delete_cyclic_buffer(&cyclic_buffer);
}

struct arg_struct {
  int val;
  int delay;
  struct cyclic_int_buffer *cyclic_buffer;
};

void *put_delayed(void *arg) {
  struct arg_struct *arg_s = (struct arg_struct *) arg;
  sleep(arg_s->delay);
  put(arg_s->cyclic_buffer, arg_s->val);
  return NULL;
}

void *get_delayed(void *arg) {
  struct arg_struct *arg_s = (struct arg_struct *) arg;
  sleep(arg_s->delay);
  arg_s->val = get(arg_s->cyclic_buffer);
  return NULL;
}
  
void test_empty_get() {
  pthread_t putter;
  struct cyclic_int_buffer cyclic_buffer;
  size_t cap = 3;
  int rc = create_cyclic_int_buffer(&cyclic_buffer, cap);
  CU_ASSERT_EQUAL(rc, 0);
  struct arg_struct arg;
  arg.val = 11;
  arg.delay = 1;
  arg.cyclic_buffer=&cyclic_buffer;
  pthread_create(&putter, NULL, put_delayed, &arg);
  printf("calling slow get()\n");
  int x = get(&cyclic_buffer);
  printf("get()->x=%d (11 expected)\n", x);
  CU_ASSERT_EQUAL(x, 11);
  pthread_join(putter, (void **) NULL);
}

void test_full_put() {
  pthread_t getter;
  struct cyclic_int_buffer cyclic_buffer;
  size_t cap = 3;
  int rc = create_cyclic_int_buffer(&cyclic_buffer, cap);
  CU_ASSERT_EQUAL(rc, 0);
  for (int i = 0; i < 3; i++) {
    put(&cyclic_buffer, i+10);
  }
  struct arg_struct arg;
  arg.delay = 1;
  arg.cyclic_buffer=&cyclic_buffer;
  pthread_create(&getter, NULL, get_delayed, &arg);
  printf("calling slow put:\n");
  put(&cyclic_buffer, 13);
  printf("put done\n");
  for (int i = 0; i < 3; i++) {
    int x = get(&cyclic_buffer);
    CU_ASSERT_EQUAL(x, 11+i);
  }
  pthread_join(getter, (void **) NULL);
  CU_ASSERT_EQUAL(arg.val, 10);
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
  if ((NULL == CU_add_test(pSuite, "", test_empty_cyclic_buffer))
      || (NULL == CU_add_test(pSuite, "", test_one_element_cyclic_buffer))
      || (NULL == CU_add_test(pSuite, "", test_cyclic))
      || (NULL == CU_add_test(pSuite, "", test_empty_get))
      || (NULL == CU_add_test(pSuite, "", test_full_put))
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
