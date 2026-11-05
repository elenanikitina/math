#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_atan_numbers) {
  double test_values[] = {0.000001, -0.5, 0.5,      1,        -1,
                          0.01,     1.00, INFINITY, -INFINITY};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = atan(val);
    long double my_result = s21_atan(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "atan(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_atan_pi) {
  double test_values[] = {S21_PI / 4, -S21_PI / 4, S21_PI / 6, -S21_PI / 6,
                          0.0};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    double val = test_values[i];
    double std_result = atan(val);
    long double my_result = s21_atan(val);
    long double diff = fabsl(std_result - my_result);

    ck_assert_msg(diff < EPSILON,
                  "atan(%f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
                  (long double)std_result, my_result, diff);
  }
}
END_TEST

START_TEST(test_atan_nan) {
  double nan = NAN;
  long double my_result = s21_atan(nan);
  ck_assert_msg(isnan(my_result), "s21_atan(NaN) should return NaN");
}
END_TEST

/*START_TEST(test_atan_negatv_inf) {
    double negatv_inf = -INFINITY;
    long double my_result = s21_atan(negatv_inf);
    ck_assert_msg(isnan(my_result), "s21_atan(-inf) should return NaN");}
END_TEST

START_TEST(test_atan_positv_inf) {
    double positv_inf = INFINITY;
    long double my_result = s21_atan(positv_inf);
    ck_assert_msg(isnan(my_result), "s21_atan(inf) should return NaN");}
END_TEST
*/
Suite* atan_suite(void) {
  Suite* s = suite_create("s21_atan");
  TCase* tc = tcase_create("Core");

  // Добавляем все тесты
  tcase_add_test(tc, test_atan_numbers);
  tcase_add_test(tc, test_atan_pi);
  tcase_add_test(tc, test_atan_nan);
  //  tcase_add_test(tc, test_atan_out_of_range);
  //  tcase_add_test(tc, test_atan_negatv_inf);
  //  tcase_add_test(tc, test_atan_positv_inf);
  suite_add_tcase(s, tc);
  return s;
}