#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_log_numbers) {
  double test_values[] = {0.000002, 0.012345, 1.00, 1.678901,   100.00,
                          42000,    1e-10,    1e16, 42000000000};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = log(val);
    long double my_result = s21_log(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "log(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_log_nan) {
  double nan = NAN;
  long double my_result = s21_log(nan);
  ck_assert_msg(isnan(my_result), "s21_log(NaN) should return NaN");
}
END_TEST

START_TEST(test_log_inf) {
  double inf = INFINITY;
  long double my_result = s21_log(inf);
  double std_result = log(inf);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

START_TEST(test_log_negatv) {
  double negatv = -5;
  long double my_result = s21_log(negatv);
  ck_assert_msg(isnan(my_result), "s21_log(negativ number) must return NaN");
}
END_TEST

START_TEST(test_log_DBL_MAX) {
  double very_big = DBL_MAX;
  long double my_result = s21_log(very_big);
  double std_result = log(very_big);
  long double diff = fabsl(std_result - my_result);
  ck_assert_msg(diff < EPSILON,
                "log(%f) failed: expected %.15Lf, got %.15Lf, diff %Le",
                very_big, (long double)std_result, my_result, diff);
}
END_TEST

START_TEST(test_log_zero) {
  double zero = 0;
  long double my_result = s21_log(zero);
  double std_result = log(zero);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

START_TEST(test_log_one) {
  double one = 1;
  long double my_result = s21_log(one);
  double std_result = log(one);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

Suite* log_suite(void) {
  Suite* s = suite_create("s21_log");
  TCase* tc = tcase_create("Core");

  // Добавляем все тесты
  tcase_add_test(tc, test_log_numbers);
  tcase_add_test(tc, test_log_nan);
  tcase_add_test(tc, test_log_inf);
  tcase_add_test(tc, test_log_negatv);
  tcase_add_test(tc, test_log_DBL_MAX);
  tcase_add_test(tc, test_log_zero);
  tcase_add_test(tc, test_log_one);

  suite_add_tcase(s, tc);
  return s;
}