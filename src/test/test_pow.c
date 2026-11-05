#include <check.h>
#include <math.h>

#include "s21_math.h"

START_TEST(test_pow_numbers_positive) {
  double test_values[] = {0.002, 1.00, 1.678901};
  double test_values_exp[] = {1, 2, 5};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    for (int j = 0; j < num_tests; j++) {
      double val = test_values[i];
      double exp = test_values_exp[j];

      double std_result = pow(val, exp);
      long double my_result = s21_pow(val, exp);
      long double diff = fabsl(std_result - my_result);

      ck_assert_msg(diff < EPSILON,
                    "pow(%f) failed: expected %.15Lf, got %.15Lf, diff %Le",
                    val, (long double)std_result, my_result, diff);
    }
  }
}
END_TEST

START_TEST(test_pow_numbers_negative) {
  double test_values[] = {-0.002, -1.00, -1.678901};
  double test_values_exp[] = {1, 2, 5};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    for (int j = 0; j < num_tests; j++) {
      double val = test_values[i];
      double exp = test_values_exp[j];

      double std_result = pow(val, exp);
      long double my_result = s21_pow(val, exp);
      long double diff = fabsl(std_result - my_result);

      ck_assert_msg(diff < EPSILON,
                    "pow(%f) failed: expected %.15Lf, got %.15Lf, diff %Le",
                    val, (long double)std_result, my_result, diff);
    }
  }
}
END_TEST

START_TEST(test_pow_noninteger_exp) {
  double test_values[] = {0.002, 1.00, 2.678, 100};
  double test_values_exp[] = {1.55, 2.07, 5.01};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    for (int j = 0; j < num_tests; j++) {
      double val = test_values[i];
      double exp = test_values_exp[j];

      double std_result = pow(val, exp);
      long double my_result = s21_pow(val, exp);
      long double diff = fabsl(std_result - my_result);

      ck_assert_msg(
          diff < EPSILON,
          "pow(%f ^ %f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
          exp, (long double)std_result, my_result, diff);
    }
  }
}
END_TEST

START_TEST(test_pow_big_numbers) {
  double test_values[] = {2e16, 1e26};
  double test_values_exp[] = {1.55, 2.07, 5.01};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    for (int j = 0; j < num_tests; j++) {
      double val = test_values[i];
      double exp = test_values_exp[j];

      double std_result = pow(val, exp);
      long double my_result = s21_pow(val, exp);
      long double relative_diff = fabsl((std_result - my_result) / std_result);

      ck_assert_msg(
          relative_diff < EPSILON,
          "pow(%f ^ %f) failed: expected %.15Lf, got %.15Lf, diff %Le", val,
          exp, (long double)std_result, my_result, relative_diff);
    }
  }
}
END_TEST

// NAN
START_TEST(test_pow_base_isnan) {
  double nan = NAN;

  long double my_result = s21_pow(nan, 5);
  ck_assert_msg(isnan(my_result), "s21_pow(NAN, ...) should return NaN");
}
END_TEST

START_TEST(test_pow_exp_isnan) {
  double nan = NAN;

  long double my_result = s21_pow(5, nan);
  ck_assert_msg(isnan(my_result), "s21_pow(..., NAN) should return NaN");
}
END_TEST

START_TEST(test_pow_nan) {
  double nan = NAN;

  long double my_result = s21_pow(nan, nan);
  ck_assert_msg(isnan(my_result), "s21_pow(NAN, NAN) should return NaN");
}
END_TEST

// zero
START_TEST(test_pow_zero_in_zero) {
  long double my_result = s21_pow(0, 0);
  ck_assert_ldouble_eq(my_result, 1);
}
END_TEST

START_TEST(test_pow_zero_in_positive) {
  long double my_result = s21_pow(0, 5);
  ck_assert_ldouble_eq(my_result, 0);
}
END_TEST

START_TEST(test_pow_zero_in_negative) {
  long double my_result = s21_pow(0, -5);
  ck_assert_msg(isinf(my_result), "s21_pow(0,-5) must return INF");
}
END_TEST

// exp is infinity
START_TEST(test_pow_integer_in_infinity) {
  double inf = INFINITY;
  long double my_result = s21_pow(2, inf);
  ck_assert_msg(isinf(my_result), "s21_pow(2,inf) must return INF");
}
END_TEST

START_TEST(test_pow_noninteger_in_infinity) {
  double inf = INFINITY;
  long double my_result = s21_pow(0.2, inf);
  ck_assert_ldouble_eq(my_result, 0);
}
END_TEST

START_TEST(test_pow_one_in_infinity) {
  double inf = INFINITY;
  long double my_result = s21_pow(1, inf);
  ck_assert_ldouble_eq(my_result, 1);
}
END_TEST

START_TEST(test_pow_one_in_negative_infinity) {
  double inf = INFINITY;
  long double my_result = s21_pow(1, -inf);
  ck_assert_ldouble_eq(my_result, 1);
}
END_TEST

START_TEST(test_pow_integer_in_negative_infinity) {
  double inf = -INFINITY;
  long double my_result = s21_pow(2, inf);
  ck_assert_ldouble_eq(my_result, 0);
}
END_TEST

START_TEST(test_pow_noninteger_in_negative_infinity) {
  double inf = INFINITY;
  long double my_result = s21_pow(0.2, -inf);
  ck_assert_msg(isinf(my_result), "s21_pow(0.2,-inf) must return INF");
}
END_TEST

// base is IFINITY
START_TEST(test_pow_infinity_in_positive_integer) {
  double inf = INFINITY;
  long double my_result = s21_pow(inf, 5);
  ck_assert_msg(isinf(my_result), "s21_pow(inf, 5) must return INF");
}
END_TEST

START_TEST(test_pow_infinity_in_negative_integer) {
  double inf = INFINITY;
  long double my_result = s21_pow(inf, -5);
  ck_assert_ldouble_eq(my_result, 0);
}
END_TEST

START_TEST(test_pow_negative_infinity_in_even) {
  double inf = INFINITY;
  long double my_result = s21_pow(-inf, 2);
  ck_assert_msg(isinf(my_result), "s21_pow(-inf, 2) must return INF");
}
END_TEST

START_TEST(test_pow_negative_infinity_in_odd) {
  double inf = INFINITY;
  long double my_result = s21_pow(-inf, 3);
  ck_assert_msg(isinf(my_result) && my_result < 0,
                "s21_pow(-inf, 3) must return -INF");
}
END_TEST

// base is negative and exp is non-integer
START_TEST(test_pow_bad_numbers) {
  double test_values[] = {-0.002, -1.00, -678901};
  double test_values_exp[] = {1.5, 25.5, 5.01};
  int num_tests = sizeof(test_values) / sizeof(test_values[0]);

  for (int i = 0; i < num_tests; i++) {
    for (int j = 0; j < num_tests; j++) {
      double val = test_values[i];
      double exp = test_values_exp[j];

      long double my_result = s21_pow(val, exp);

      ck_assert_msg(isnan(my_result), "s21_pow(NAN) should return NaN");
    }
  }
}
END_TEST

/*
START_TEST(test_pow_inf) {
    double inf = INFINITY;
    long double my_result = s21_pow(inf);
    double std_result = pow(inf);
    ck_assert_ldouble_eq(my_result, std_result);}
END_TEST

START_TEST(test_pow_negatv) {
    double negatv = -5;
    long double my_result = s21_pow(negatv);
    ck_assert_msg(isnan(my_result), "s21_pow(negativ number) must return NaN");}
END_TEST

START_TEST(test_pow_DBL_MAX) {
    double very_big = DBL_MAX;
    long double my_result = s21_pow(very_big);
    double std_result = pow(very_big);
    long double diff = fabsl(std_result - my_result);
    ck_assert_msg(diff < EPSILON, "pow(%f) failed: expected %.15Lf, got %.15Lf,
diff %Le", very_big, (long double)std_result, my_result, diff);} END_TEST

START_TEST(test_pow_zero) {
    double zero = 0;
    long double my_result = s21_pow(zero);
    double std_result = pow(zero);
    ck_assert_ldouble_eq(my_result, std_result);}
END_TEST

START_TEST(test_pow_one) {
    double one = 1;
    long double my_result = s21_pow(one);
    double std_result = pow(one);
    ck_assert_ldouble_eq(my_result, std_result);}
END_TEST
*/
Suite* pow_suite(void) {
  Suite* s = suite_create("s21_pow");
  TCase* tc = tcase_create("Core");

  // Добавляем все тесты
  tcase_add_test(tc, test_pow_numbers_positive);
  tcase_add_test(tc, test_pow_numbers_negative);
  tcase_add_test(tc, test_pow_noninteger_exp);
  tcase_add_test(tc, test_pow_big_numbers);
  tcase_add_test(tc, test_pow_base_isnan);
  tcase_add_test(tc, test_pow_exp_isnan);
  tcase_add_test(tc, test_pow_nan);
  tcase_add_test(tc, test_pow_zero_in_zero);
  tcase_add_test(tc, test_pow_zero_in_positive);
  tcase_add_test(tc, test_pow_zero_in_negative);
  tcase_add_test(tc, test_pow_integer_in_infinity);
  tcase_add_test(tc, test_pow_noninteger_in_infinity);
  tcase_add_test(tc, test_pow_one_in_infinity);
  tcase_add_test(tc, test_pow_one_in_negative_infinity);
  tcase_add_test(tc, test_pow_integer_in_negative_infinity);
  tcase_add_test(tc, test_pow_noninteger_in_negative_infinity);
  tcase_add_test(tc, test_pow_bad_numbers);
  tcase_add_test(tc, test_pow_infinity_in_positive_integer);
  tcase_add_test(tc, test_pow_infinity_in_negative_integer);
  tcase_add_test(tc, test_pow_negative_infinity_in_even);
  tcase_add_test(tc, test_pow_negative_infinity_in_odd);

  /*  tcase_add_test(tc, test_pow_inf);
   tcase_add_test(tc, test_pow_negatv);
   tcase_add_test(tc, test_pow_DBL_MAX);
   tcase_add_test(tc, test_pow_zero);
   tcase_add_test(tc, test_pow_one);
 */
  suite_add_tcase(s, tc);
  return s;
}