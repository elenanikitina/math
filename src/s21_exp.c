#include "s21_math.h"

// Return e raised to a given power
long double s21_exp(double x) {
  long double result = 1;
  int special_case = 0;
  // special cases:
  if (x == 0 || s21_fabs(x) > 709.7827128933840299 || x == S21_NAN ||
      x == S21_INF || x == -S21_INF) {
    special_case = 1;
    if (s21_isnan(x))
      result = S21_NAN;
    else if (x == 0)
      result = 1;
    else if (x > 709.7827128933840299 || x == S21_INF)
      result = S21_INF;
    else if (x < -709.7827128933840299 || x == -S21_INF)
      result = 0.0L;
  }

  if (!special_case) {
    int x_is_negative = 0;
    if (x < 0) {
      x = -x;
      x_is_negative = 1;
    }

    // divide to int and float part
    int integer_part = (int)x;
    long double float_part = x - integer_part;

    // calculate float with Teylor
    result = 1;
    long double add = 1;
    int n = 0;

    while (add > 1e-16) {
      n++;
      add = add * float_part / n;
      result = result + add;
    }

    // calculate euler in int power = result_int. And multiply power_of_int with
    // the previous results
    long double base = EULER_E;
    long double result_int = 1;
    int i = integer_part;
    while (i > 0) {
      if (i % 2 == 0) {
        base = base * base;
        i = i / 2;
      } else if (i % 2 > 0) {
        i = i - 1;
        result_int = result_int * base;
      }
    }
    result = result * result_int;
    result = (x_is_negative) ? 1 / result : result;
  }
  return result;
}