#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_ceil_simple) {
  double test_values[] = {0.00,   0.0001,  -0.000002, 1.00,   -1.00,
                          1.01,   -0.99,   -1.01,     42.000, 41.099,
                          -42.01, DBL_MIN, DBL_MAX};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    long double my_result = s21_ceil(val);
    double std_result = ceil(val);

    ck_assert_ldouble_eq(my_result, std_result);
  }
}
END_TEST

START_TEST(test_ceil_nan) {
  double nan = NAN;
  long double my_result = s21_ceil(nan);

  ck_assert_msg(isnan(my_result), "s21_ceil(NAN) should return NaN");
}
END_TEST

START_TEST(test_ceil_positiv_infinity) {
  double positive_inf = INFINITY;
  long double my_result = s21_ceil(positive_inf);
  double std_result = ceil(positive_inf);

  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

START_TEST(test_ceil_negativ_infinity) {
  double negativ_inf = -INFINITY;
  long double my_result = s21_ceil(negativ_inf);
  double std_result = ceil(negativ_inf);

  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

Suite* ceil_suite(void) {
  Suite* s = suite_create("s21_ceil");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_ceil_simple);
  tcase_add_test(tc, test_ceil_nan);
  tcase_add_test(tc, test_ceil_positiv_infinity);
  tcase_add_test(tc, test_ceil_negativ_infinity);

  suite_add_tcase(s, tc);
  return s;
}