#include "s21_math.h"

// computes arctg
long double s21_atan(double x) {
  long double result;
  int minus = 1;
  if (x < 0) {
    minus = -1;
    x = -x;
  }
  long double new_add = x;
  if (s21_isnan(x))
    result = S21_NAN;
  else if (s21_isinf(x)) {
    result = S21_PI / 2;
  }
  // Main part
  else {
    result = x;
    if (s21_fabs(x) > 1) {
      result = minus * S21_PI / 2 - s21_atan(1 / x);
    }
    // Taylor
    else {
      int n = 1;
      while (s21_fabs(new_add) > EPSILON) {
        new_add = -1 * new_add * x * x * (2 * n - 1) / (2.0 * n + 1);
        result += new_add;
        n++;
      }
    }
  }
  return minus * result;
}
