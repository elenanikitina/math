#include "s21_math.h"

// returns the nearest integer not less than the given value
long double s21_ceil(double x) {
  long double result = 0;

  if (s21_isnan(x) || s21_isinf(x))
    result = x;
  else if (s21_fabs(x) >= 1 && s21_fabs(x - (long double)(long long)x) < 1e-16)
    result = x;
  else if (x > (long double)S21_LONG_LONG_MAX)
    result = x;
  else if (x < (long double)S21_LONG_LONG_MIN)
    result = x;
  else if (x > 0)
    result = (long double)(long long)x + 1;
  else if (x <= 0)
    result = (long double)(long long)x;
  return result;
}
