#include <float.h>  //LDBL_MIN LDBL_MAX
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

// computes natural logarithm
long double s21_log(double x) {
  long double result = x;
  double u;
  if (x < 0 || s21_isnan(x))
    result = S21_NAN;
  else if (x == 0)
    result = -S21_INF;
  else if (x == 1)
    result = 0;
  else if (s21_isinf(x))
    result = S21_INF;
  else {
    long double new_add;

    // extract 2^x
    int n1 = 0;
    int n2 = 0;
    if (x >= 2) {
      while (x > 2) {
        x /= 2;
        n1++;
      }
    } else if (x < 1) {
      while (x < 1) {
        x *= 2;
        n2++;
      }
    }
    // считаем ln(мантиссы) разложением про ряду Маклорена
    u = (x - 1) / (x + 1);
    result = u;
    new_add = u;
    int k = 1;
    while (s21_fabs(new_add) > 1e-16) {
      new_add = new_add * u * u * (2 * k - 1) / (2 * k + 1);
      result += new_add;
      k++;
    }
    result = 2 * result;
    result = (n1 != 0) ? result + n1 * LN2 : result - n2 * LN2;
  }
  return result;
}
