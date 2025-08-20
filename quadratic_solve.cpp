#include <assert.h>
#include <math.h>
#include "quadratic_main.hpp"
#include "quadratic_utils.hpp"

void GetQuadraticSolution(const double a, const double b, const double c,
                          double *x1, double *x2,
                          AMOUNT_OF_SOLUTIONS *number_of_solutions);

void GetLinearSolution(const double b, const double c, double *x1,
                  AMOUNT_OF_SOLUTIONS *number_of_solutions);

void SolveEquation(SquareEquation *quad) {
  assert(quad);
  if (ZeroComp(quad->a) == 0)
    GetLinearSolution(quad->b, quad->c, &quad->x1, &quad->number_of_solutions);
  else
    GetQuadraticSolution(quad->a, quad->b, quad->c,
                         &quad->x1, &quad->x2,
                         &quad->number_of_solutions);
  RemoveNegativeZero(&quad->x1);
  RemoveNegativeZero(&quad->x2);
}

void GetQuadraticSolution(const double a, const double b, const double c,
                          double *x1, double *x2,
                          AMOUNT_OF_SOLUTIONS *number_of_solutions) {
  assert(x1 && x2 && number_of_solutions);
  double diskr = b * b - 4 * a * c;
  double sq_diskr = sqrt(diskr);
  if (ZeroComp(diskr) < 0) {
    *number_of_solutions = zero_solutions;
  } else if (ZeroComp(diskr) == 0) {
    *x1 = -b / 2 / a;
    *number_of_solutions = one_solution;
  } else {
    *x1 = (-b - sq_diskr) / 2 / a;
    *x2 = (-b + sq_diskr) / 2 / a;
    *number_of_solutions = two_solutions;
  }
}

void GetLinearSolution(const double b, const double c, double *x1,
                  AMOUNT_OF_SOLUTIONS *number_of_solutions) {
  assert(x1  && number_of_solutions);
  if (ZeroComp(b) == 0) {
    if (ZeroComp(c) == 0)
      *number_of_solutions = inf_solutions;
    else
      *number_of_solutions = zero_solutions;
  } else {
    *x1 = -c / b;
    *number_of_solutions = one_solution;
  }
}
