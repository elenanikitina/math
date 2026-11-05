#include "s21_math.h"

// computes arcsin
long double s21_asin(double x) {
  long double result;
  int minus = 1;
  if (x < 0) {
    minus = -1;
    x = -x;
  }
  long double new_add = x;
  if (s21_fabs(x) > 1 || s21_isnan(x)) {
    result = S21_NAN;
  } else {
    result = x;
    if (s21_fabs(x) > 0.5) {
      result = S21_PI / 2 - 2 * s21_asin(s21_sqrt((1 - x) / 2));
    } else {
      int n = 1;
      while (s21_fabs(new_add) > EPSILON) {
        new_add = new_add * x * x *
                  (((2 * n - 1) * (2 * n - 1)) / (2.0 * n * (2 * n + 1)));
        result += new_add;
        n++;
      }
    }
  }
  return minus * result;
}