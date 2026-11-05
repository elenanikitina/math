#include "s21_math.h"

// computes tan
long double s21_tan(double x) {
  x = s21_fmod(x, S21_PI);
  if (x > S21_PI / 2) x = x - S21_PI;
  if (x < -S21_PI / 2) x = x + S21_PI;
  long double result = s21_sin(x) / s21_cos(x);
  return result;
}
