#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_fabs_simple) {
  double test_values[] = {0.00,   0.0001,  -0.000002, 1.00,   -1.00,
                          1.01,   -0.99,   -1.01,     42.000, 41.099,
                          -42.01, DBL_MIN, DBL_MAX};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    long double my_result = s21_fabs(val);
    double std_result = fabs(val);

    ck_assert_ldouble_eq(my_result, std_result);
  }
}
END_TEST

START_TEST(test_fabs_nan) {
  double nan = NAN;
  long double my_result = s21_fabs(nan);

  ck_assert_msg(isnan(my_result), "s21_fabs(NAN) should return NaN");
}
END_TEST

START_TEST(test_fabs_positiv_infinity) {
  double positive_inf = INFINITY;
  long double my_result = s21_fabs(positive_inf);
  double std_result = fabs(positive_inf);

  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

START_TEST(test_fabs_negativ_infinity) {
  double negativ_inf = -INFINITY;
  long double my_result = s21_fabs(negativ_inf);
  double std_result = fabs(negativ_inf);

  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

Suite* fabs_suite(void) {
  Suite* s = suite_create("s21_fabs");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_fabs_simple);
  tcase_add_test(tc, test_fabs_nan);
  tcase_add_test(tc, test_fabs_positiv_infinity);
  tcase_add_test(tc, test_fabs_negativ_infinity);

  suite_add_tcase(s, tc);
  return s;
}