#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_abs_simple) {
  int test_values[] = {0,     1,      -2,    100,     -99,    -0,
                       42000, -41099, -4201, INT_MIN, INT_MAX};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    int val = test_values[i];
    int my_result = s21_abs(val);
    int std_result = abs(val);

    ck_assert_int_eq(my_result, std_result);
  }
}
END_TEST

Suite* abs_suite(void) {
  Suite* s = suite_create("s21_abs");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_abs_simple);

  suite_add_tcase(s, tc);
  return s;
}