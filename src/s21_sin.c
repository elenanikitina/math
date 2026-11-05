#include "s21_math.h"

/*/ computes factorial
long long s21_factorial(int x) {
  long long result = 1;
  int i = 0;

  if (x < 0)
    result = 0;
  else {
    while (i < x) {
      i++;
      result = result * i;
    }
  }
  return result;
}*/

// computes sine
long double s21_sin(double x) {
  x = s21_fmod(x, (2 * S21_PI));
  if (x > S21_PI) x = x - 2 * S21_PI;
  if (x < -S21_PI) x = x + 2 * S21_PI;

  long double result = x;
  long double new_add = x;
  int n = 1;
  int m;

  while (s21_fabs(new_add) > EPSILON) {
    m = 2 * n + 1;
    // new_add = -1 * s21_pow(x,m) / s21_factorial(m);
    new_add = -1 * new_add * x * x / ((m - 1) * m);
    n++;
    result += new_add;
  }
  return result;
}
