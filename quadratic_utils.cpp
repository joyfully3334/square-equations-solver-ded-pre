#include <assert.h>
#include <math.h>
#include <string.h>

#include "quadratic_utils.hpp"

const double EPS = 1e-5;

int DoubleComp(const double num1, const double num2) {
  if (num1 - num2 < -EPS)
    return -1;
  else if (fabs(num1 - num2) <= EPS)
    return 0;
  else
    return 1;
}

void RemoveNegativeZero(double *const num) {
  assert(num);

  *num = (DoubleComp(*num, 0.) ? *num : fabs(*num));
}

int CheckFlag(int argc, char **argv, const char *flag) {
  for (int i = 0; i < argc; ++i) {
    if (!strcmp(argv[i], flag))
      return 1;
  }

  return 0;
}

int QuadraticComp(const SquareEquation quad1, const SquareEquation quad2) {
  if (DoubleComp(quad1.a, quad2.a) || DoubleComp(quad1.b, quad2.b) ||
      DoubleComp(quad1.c, quad2.c) ||
      DoubleComp(quad1.number_of_solutions, quad2.number_of_solutions))
    return 1;
  switch (quad1.number_of_solutions) {
  case zero_solutions:
    return 0;
  case one_solution:
    return DoubleComp(quad1.x1, quad2.x1);
  case two_solutions:
    return DoubleComp(quad1.x1, quad2.x1) || DoubleComp(quad1.x2, quad2.x2);
  case inf_solutions:
    return 0;
  case undefined_solutions:
  default:
    return 1;
  }
}
