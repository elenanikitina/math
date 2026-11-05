#include "s21_math.h"

// computes absolute value of an integer value
//  INT_MIN undefined behaiour
int s21_abs(int x) { return ((x < 0) ? -x : x); }