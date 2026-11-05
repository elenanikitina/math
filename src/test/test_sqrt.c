#include <check.h>
#include <math.h>

#include "s21_math.h"

// #define EPSILON 1e-6

START_TEST(test_sqrt_numbers) {
  // double inf = 1.0L / 0.0L;
  // double nan = 0.0L / 0.0L;

  double test_values[] = {0.000001, 0.01,  1.00,       1.6,    4.00,
                          10.00,    16.00, 25.00,      100.00, 42000,
                          1e-10,    1e16,  42000000000};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = sqrt(val);
    long double my_result = s21_sqrt(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "sqrt(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_sqrt_nan) {
  double nan = NAN;
  long double my_result = s21_sqrt(nan);
  ck_assert_msg(isnan(my_result), "s21_sqrt(NaN) should return NaN");
}
END_TEST

START_TEST(test_sqrt_negatv_inf) {
  double negatv_inf = -INFINITY;
  long double my_result = s21_sqrt(negatv_inf);
  ck_assert_msg(isnan(my_result), "s21_sqrt(negativ inf) should return NaN");
}
END_TEST

START_TEST(test_sqrt_positv_inf) {
  double inf = INFINITY;
  long double my_result = s21_sqrt(inf);
  double std_result = sqrt(inf);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

START_TEST(test_sqrt_negatv) {
  double negatv = -5;
  long double my_result = s21_sqrt(negatv);
  ck_assert_msg(isnan(my_result), "s21_sqrt(negativ number) must return NaN");
}
END_TEST

START_TEST(test_sqrt_DBL_MAX) {
  double very_big = DBL_MAX;
  long double my_result = s21_sqrt(very_big);
  double std_result = sqrt(very_big);
  long double diff = fabsl(std_result - my_result);
  long double relative_diff = fabsl(diff / std_result);
  ck_assert_msg(relative_diff < EPSILON,
                "sqrt(%f) failed: expected %.15Lf, got %.15Lf, diff %Le",
                very_big, (long double)std_result, my_result, diff);
}
END_TEST

START_TEST(test_sqrt_zero) {
  double zero = 0;
  long double my_result = s21_sqrt(zero);
  double std_result = sqrt(zero);
  ck_assert_ldouble_eq(my_result, std_result);
}
END_TEST

Suite* sqrt_suite(void) {
  Suite* s = suite_create("s21_sqrt");
  TCase* tc = tcase_create("Core");

  // Добавляем все тесты
  tcase_add_test(tc, test_sqrt_numbers);
  tcase_add_test(tc, test_sqrt_nan);
  tcase_add_test(tc, test_sqrt_negatv);
  tcase_add_test(tc, test_sqrt_negatv_inf);
  tcase_add_test(tc, test_sqrt_positv_inf);
  tcase_add_test(tc, test_sqrt_DBL_MAX);
  tcase_add_test(tc, test_sqrt_zero);

  suite_add_tcase(s, tc);
  return s;
}