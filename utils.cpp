#include <assert.h>
#include <math.h>
#include "quadratic.hpp"

int ZeroComp(const double num) {
  if (num < -EPS)
    return -1;
  else if (fabs(num - 0.) <= EPS)
    return 0;
  else
    return 1;
}

void RemoveNegativeZero(double *num) {
  assert(num);
  *num = (ZeroComp(*num) ? *num : fabs(*num));
}
