#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_fmod_simple) {
  double test_values[] = {0.00,   0.0001, 1.0000001, -0.000002, 1.00,
                          -1.00,  1.01,   -0.99,     -1.01,     42.000,
                          41.099, -42.01, DBL_MIN};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    long double my_result = s21_fmod(val, S21_PI);
    double std_result = fmod(val, S21_PI);

    ck_assert_ldouble_eq(my_result, std_result);
  }
}
END_TEST

START_TEST(test_fmod_big_numbers) {
  double test_values[] = {75000.001, 1e10,  1e15,   1e20,   1e100,
                          1e300,     -1e10, -1e100, DBL_MAX};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    long double my_result = s21_fmod(val, S21_PI);
    double std_result = fmod(val, S21_PI);
    long double relative_diff = s21_fabs((my_result - std_result) / std_result);

    ck_assert_msg(relative_diff < EPSILON,
                  "fmod(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, relative_diff);
  }
}
END_TEST

START_TEST(test_fmod_nan) {
  double nan = NAN;
  long double my_result = s21_fmod(nan, S21_PI);

  ck_assert_msg(isnan(my_result), "s21_fmod(NAN, S21_PI) should return NaN");
}
END_TEST

START_TEST(test_fmod_positiv_infinity) {
  double inf = INFINITY;
  long double my_result = s21_fmod(inf, S21_PI);

  ck_assert_msg(isnan(my_result), "s21_fmod(INF, x) should return NaN");
}
END_TEST

START_TEST(test_fmod_negativ_infinity) {
  double inf = -INFINITY;
  long double my_result = s21_fmod(inf, S21_PI);

  ck_assert_msg(isnan(my_result), "s21_fmod(-INF, x) should return NaN");
}
END_TEST

START_TEST(test_fmod_devisor_is_infinity) {
  double inf = INFINITY;
  long double my_result = s21_fmod(S21_PI, inf);

  ck_assert_msg(isnan(my_result), "s21_fmod( x , INF) should return NaN");
}
END_TEST

Suite* fmod_suite(void) {
  Suite* s = suite_create("s21_fmod");
  TCase* tc = tcase_create("Core");

  tcase_add_test(tc, test_fmod_simple);
  tcase_add_test(tc, test_fmod_big_numbers);
  tcase_add_test(tc, test_fmod_nan);
  tcase_add_test(tc, test_fmod_positiv_infinity);
  tcase_add_test(tc, test_fmod_negativ_infinity);
  tcase_add_test(tc, test_fmod_devisor_is_infinity);
  suite_add_tcase(s, tc);
  return s;
}
