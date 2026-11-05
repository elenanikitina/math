#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_asin_numbers) {
  double test_values[] = {0.000001, -0.5, 0.5, 1, -1, 0.01, 1.00};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = asin(val);
    long double my_result = s21_asin(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "asin(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_asin_pi) {
  double test_values[] = {S21_PI / 4, -S21_PI / 4, S21_PI / 6, -S21_PI / 6,
                          0.0};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = asin(val);
    long double my_result = s21_asin(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "asin(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_asin_out_of_range) {
  double test_values[] = {S21_PI, -S21_PI, S21_PI / 2, -S21_PI / 2,
                          100,    -2,      15.0};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);
  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    long double my_result = s21_asin(val);
    ck_assert_msg(isnan(my_result), "s21_asin(inf) should return NaN");
  }
}
END_TEST

START_TEST(test_asin_nan) {
  double nan = NAN;
  long double my_result = s21_asin(nan);
  ck_assert_msg(isnan(my_result), "s21_asin(NaN) should return NaN");
}
END_TEST

START_TEST(test_asin_negatv_inf) {
  double negatv_inf = -INFINITY;
  long double my_result = s21_asin(negatv_inf);
  ck_assert_msg(isnan(my_result), "s21_asin(-inf) should return NaN");
}
END_TEST

START_TEST(test_asin_positv_inf) {
  double positv_inf = INFINITY;
  long double my_result = s21_asin(positv_inf);
  ck_assert_msg(isnan(my_result), "s21_asin(inf) should return NaN");
}
END_TEST

Suite* asin_suite(void) {
  Suite* s = suite_create("s21_asin");
  TCase* tc = tcase_create("Core");

  // Добавляем все тесты
  tcase_add_test(tc, test_asin_numbers);
  tcase_add_test(tc, test_asin_pi);
  tcase_add_test(tc, test_asin_nan);
  tcase_add_test(tc, test_asin_out_of_range);
  tcase_add_test(tc, test_asin_negatv_inf);
  tcase_add_test(tc, test_asin_positv_inf);
  suite_add_tcase(s, tc);
  return s;
}