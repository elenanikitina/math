#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_tan_numbers) {
  double test_values[] = {0.000001, 0.01, 1.00,   1.5,   4.00, 10.00, 16.00,
                          25.00,    -5,   100.00, 42000, 1e-8, 1e10};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = tan(val);
    long double my_result = s21_tan(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "tan(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_tan_pi) {
  double test_values[] = {S21_PI, S21_PI / 3, S21_PI / 6, -S21_PI / 3, 0.0};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = tan(val);
    long double my_result = s21_tan(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "tan(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_tan_nan) {
  double nan = NAN;
  long double my_result = s21_tan(nan);
  ck_assert_msg(isnan(my_result), "s21_tan(NaN) should return NaN");
}
END_TEST

START_TEST(test_tan_negatv_inf) {
  double negatv_inf = -INFINITY;
  long double my_result = s21_tan(negatv_inf);
  ck_assert_msg(isnan(my_result), "s21_tan(-inf) should return NaN");
}
END_TEST

START_TEST(test_tan_positv_inf) {
  double positv_inf = INFINITY;
  long double my_result = s21_tan(positv_inf);
  ck_assert_msg(isnan(my_result), "s21_tan(inf) should return NaN");
}
END_TEST

Suite* tan_suite(void) {
  Suite* s = suite_create("s21_tan");
  TCase* tc = tcase_create("Core");

  // Добавляем все тесты
  tcase_add_test(tc, test_tan_numbers);
  tcase_add_test(tc, test_tan_pi);
  tcase_add_test(tc, test_tan_nan);
  tcase_add_test(tc, test_tan_negatv_inf);
  tcase_add_test(tc, test_tan_positv_inf);
  suite_add_tcase(s, tc);
  return s;
}