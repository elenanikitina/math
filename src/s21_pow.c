#include "s21_math.h"

long double s21_pow(double base, double exp) {
  long double result = 1;
  int negativ_exp = 0;

  if (s21_isnan(base) || s21_isnan(exp))
    result = S21_NAN;
  else if (base == 0) {
    if (exp == 0)
      result = 1;
    else if (exp < 0)
      result = S21_INF;
    else if (exp > 0)
      result = 0;
  } else if (s21_isinf(exp) && (exp > 0)) {  // степень это +бесконечность
    if (s21_fabs(base) > 1) result = S21_INF;
    if (s21_fabs(base) < 1) result = 0;
    if (s21_fabs(base) == 1) result = 1;
  } else if (s21_isinf(exp) && (exp < 0)) {  // степень это - бесконечность
    if (s21_fabs(base) > 1) result = 0;
    if (s21_fabs(base) < 1) result = S21_INF;
    if (s21_fabs(base) == 1) result = 1;
  } else if (base < 0 && !(s21_isint(exp)))  // отрицательное в дробной степени)
    result = S21_NAN;
  else if (s21_isint(exp)) {  // степень это целое число
    if (exp < 0) {
      exp = -exp;
      negativ_exp = 1;
    }
    while (exp > 0) {  // ускоренное возведение, спасет при большой степени
      if ((int)exp % 2 == 0) {
        base = base * base;
        exp = exp / 2;
      } else if ((int)exp % 2 == 1) {
        result = result * base;
        exp = exp - 1;
      }
    }
    if (negativ_exp) result = 1 / result;
  } else if (!s21_isint(exp)) {  // степень это дробное число
    if (base < 0)
      result = S21_NAN;
    else
      result = s21_exp(exp * s21_log(base));
  }
  return result;
}