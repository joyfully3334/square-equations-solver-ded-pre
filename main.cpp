#include <math.h>
#include <stdio.h>
#include "quadratic.h"

int main() {
  SquareEquation quad1 = {0., 0., 0., 0., 0., undefined_solutions};
  if (CoefErrHandler(ReadInput(&quad1)))
    return 1;

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", quad1.a,
         (quad1.b >= 0 ? '+' : '-'), fabs(quad1.b),
         (quad1.c >= 0 ? '+' : '-'), fabs(quad1.c));

  SolveEquation(&quad1);
  if (PrintResult(quad1))
    return 1;

  return 0;
}
