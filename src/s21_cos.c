#include "s21_math.h"

// computes cos
long double s21_cos(double x) {
  x = s21_fmod(x, (2 * S21_PI));
  if (x > S21_PI) x = x - 2 * S21_PI;
  if (x < -S21_PI) x = x + 2 * S21_PI;

  long double result = 1;
  long double new_add = 1;
  int n = 1;
  int m;

  while (s21_fabs(new_add) > EPSILON) {
    m = 2 * n;
    new_add = -1 * new_add * x * x / ((m - 1) * m);
    n++;
    result += new_add;
  }
  return result;
}
