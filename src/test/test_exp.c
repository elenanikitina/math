#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_exp_numbers) {
  double test_values[] = {0.000001, 0.01,  1.00,  1.6, 4.00,
                          10.00,    16.00, 25.00, -5,  100.00};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = exp(val);
    long double my_result = s21_exp(val);
    long double diff = fabsl(std_result - my_result);
    long double relative_diff = fabsl(diff / std_result);

    ck_assert_msg(relative_diff < EPSILON,
                  "exp(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_exp_bignumbers) {
  double test_values[] = {42000, 1e-10, 1e16, 42000000000};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = exp(val);
    long double my_result = s21_exp(val);
    ck_assert_int_eq(my_result, std_result);
  }
}
END_TEST

START_TEST(test_exp_nan) {
  double nan = NAN;
  long double my_result = s21_exp(nan);
  ck_assert_msg(isnan(my_result), "s21_exp(NaN) should return NaN");
}
END_TEST

START_TEST(test_exp_negatv_inf) {
  double negatv_inf = -INFINITY;
  long double my_result = s21_exp(negatv_inf);
  double std_result = exp(negatv_inf);
  long double diff = fabsl(std_result - my_result);
  ck_assert_msg(diff < EPSILON,
                "exp(-inf) failed: expected %.15Lf, got %.15Lf, diff %Le",
                (long double)std_result, my_result, diff);
}
END_TEST

START_TEST(test_exp_positv_inf) {
  double inf = INFINITY;
  long double my_result = s21_exp(inf);
  double std_result = exp(inf);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

START_TEST(test_exp_DBL_MAX) {
  double very_big = DBL_MAX;
  long double my_result = s21_exp(very_big);
  double std_result = exp(very_big);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

START_TEST(test_exp_zero) {
  double zero = 0;
  long double my_result = s21_exp(zero);
  double std_result = exp(zero);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

Suite* exp_suite(void) {
  Suite* s = suite_create("s21_exp");
  TCase* tc = tcase_create("Core");

  // Добавляем все тесты
  tcase_add_test(tc, test_exp_numbers);
  tcase_add_test(tc, test_exp_bignumbers);
  tcase_add_test(tc, test_exp_nan);
  tcase_add_test(tc, test_exp_negatv_inf);
  tcase_add_test(tc, test_exp_positv_inf);
  tcase_add_test(tc, test_exp_DBL_MAX);
  tcase_add_test(tc, test_exp_zero);

  suite_add_tcase(s, tc);
  return s;
}