#include <math.h>

#include "s21_math.h"

// remainder of the floating-point division operation
long double s21_fmod(double x, double y) {
  long double quotient;
  long double remainder;

  quotient = x / y;
  if (quotient >= 0)
    quotient = s21_floor(quotient);
  else if (quotient < 0)
    quotient = s21_ceil(quotient);
  remainder = x - (y * quotient);

  return remainder;
}