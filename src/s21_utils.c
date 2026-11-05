#include "s21_math.h"

// isinf
int s21_isinf(long double x) {
  int result = 0;

  if (x == x && x * 2 == x && x != 0) result = 1;
  return result;
}

// isnan
int s21_isnan(long double x) {
  int result = 0;

  if (x != x) result = 1;
  return result;
}

// isint
int s21_isint(long double x) {
  int result = 0;
  long double difference = s21_fabs(x - (long double)(long long)x);

  if (difference < 1e-15) result = 1;
  return result;
}