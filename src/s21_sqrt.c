#include "s21_math.h"

// computes square root
long double s21_sqrt(double x) {
  long double result;
  if (x < 0 || s21_isnan(x))
    result = 0.0L / 0.0L;
  else if (s21_isinf(x))
    result = x;
  else if (x == 0)
    result = 0;
  else {
    long double mantissa = x;
    int exponent = 0;

    while ((mantissa > 0 && mantissa < 1) || mantissa > 10) {
      if (mantissa > 10) {
        mantissa = mantissa / 10;
        exponent++;
      } else if (mantissa > 0 && mantissa < 1) {
        mantissa = mantissa * 10;
        exponent--;
      }
    }
    // считаем корень из экспоненты
    if (exponent % 2 == 0)
      exponent = exponent / 2;
    else if (exponent % 2 == 1) {
      mantissa = mantissa * 10;
      exponent = (exponent - 1) / 2;
    } else if (exponent % 2 == -1) {
      mantissa = mantissa / 10;
      exponent = (exponent + 1) / 2;
    }
    // считаем корень из мантиссы
    long double approximate = mantissa / 2;
    while (s21_fabs(approximate * approximate - mantissa) > 1e-16) {
      approximate = (approximate + mantissa / approximate) / 2;
    }
    result = approximate;
    while (exponent != 0) {
      if (exponent > 0) {
        result = result * 10;
        exponent--;
      } else {
        result = result / 10;
        exponent++;
      }
    }
  }
  return result;
}
