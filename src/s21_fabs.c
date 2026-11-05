#include "s21_math.h"

// computes absolute value of a floating-point value
long double s21_fabs(double x) { return ((x < 0) ? -x : x); }