#ifndef S21_MATH_H
#define S21_MATH_H

#include <float.h>  //LDBL_MIN LDBL_MAX
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_math.h"

#define EPSILON 1e-6
#define EULER_E 2.71828182845904523536028747
#define S21_INF (1.0L / 0.0L)
#define S21_NAN (0.0L / 0.0L)
#define LN2 0.6931471805599453094172321214581765680755001343602552L
#define S21_LONG_LONG_MAX 9223372036854775807LL
#define S21_LONG_LONG_MIN (-9223372036854775807LL - 1)
#define S21_PI 3.1415926535897932

// Computes absolute value of an integer value
int s21_abs(int x);

// Computes absolute value of an integer value
long double s21_fabs(double x);

// Returns the nearest integer not less than the given value
long double s21_ceil(double x);

// Returns the nearest integer not greater than the given value
long double s21_floor(double x);

// Computes square root
long double s21_sqrt(double x);

// Returns e raised to the given power
long double s21_exp(double x);

// Returns x raised to the given power
long double s21_pow(double base, double exp);

// Computes natural logarithm
long double s21_log(double x);

// Remainder of the floating-point division operation
long double s21_fmod(double x, double y);

// Factorial
long long s21_factorial(int x);

// Computes sine
long double s21_sin(double x);

// Computes cos
long double s21_cos(double x);

// Computes tg
long double s21_tan(double x);

// Computes arcsin
long double s21_asin(double x);

// Computes arccos
long double s21_acos(double x);

// Computes arctg
long double s21_atan(double x);

// Computes arctg
long double s21_atan(double x);

// Exponentiation
long double s21_pow(double base, double exp);

// Is inf
int s21_isinf(long double x);

// Is nan
int s21_isnan(long double x);

// Is int
int s21_isint(long double x);

#endif  // S21_MATH_H