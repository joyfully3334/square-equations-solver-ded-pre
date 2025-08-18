#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum INPUT_ERRORS {
  no_input_errors = 0,
  not_a_number    = 1,
  not_finite      = 2
};
enum PRINT_RESULTS_ERRORS {
  no_print_results_errors       = 0,
  undefined_amount_of_solutions = 1,
};
enum AMOUNT_OF_SOLUTIONS {
  undefined_solutions = -1,
  zero_solutions      =  0,
  one_solution        =  1,
  two_solutions       =  2,
  inf_solutions       =  3,
};
const double EPS = 1e-5;

struct SquareEquation {
  double a, b, c, x1, x2;
  AMOUNT_OF_SOLUTIONS number_of_solutions;
};

INPUT_ERRORS ReadCoef(double *coef, char name);

INPUT_ERRORS ReadInput(SquareEquation *quad);

int CoefErrHandler(INPUT_ERRORS read_result);

int ZeroComp(double num);

void RemoveNegativeZero(double *num);

void SolveEquation(SquareEquation *quad);

void SolveQuadratic(SquareEquation *quad);

void SolveLinear(SquareEquation *quad);

PRINT_RESULTS_ERRORS PrintResult(SquareEquation quad);

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

INPUT_ERRORS ReadCoef(double *coef, char name) {
  assert(coef);
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;
  return no_input_errors;
}

INPUT_ERRORS ReadInput(SquareEquation *quad) {
  assert(quad);
  INPUT_ERRORS ret_val = ReadCoef(&quad->a, 'a');
  if (ret_val)
    return ret_val;
  ret_val = ReadCoef(&quad->b, 'b');
  if (ret_val)
    return ret_val;
  ret_val = ReadCoef(&quad->c, 'c');
  if (ret_val)
    return ret_val;
  return no_input_errors;
}

int CoefErrHandler(INPUT_ERRORS read_result) {
  if (read_result == not_a_number) {
    printf("Incorrect input data: Provided symbols is not a number\n");
    return 1;
  } else if (read_result == not_finite) {
    printf("Incorrect input data: Provided number is not finite\n");
    return 1;
  }
  return 0;
}

int ZeroComp(double num) {
  if (num < -EPS)
    return -1;
  else if (fabs(num - 0.) <= EPS)
    return 0;
  else
    return 1;
}

void RemoveNegativeZero(double *num) {
  *num = ((*num == -0.) ? 0. : *num);
}

void SolveEquation(SquareEquation *quad) {
  assert(quad);
  if (ZeroComp(quad->a) == 0)
    SolveLinear(quad);
  else
    SolveQuadratic(quad);
  RemoveNegativeZero(&quad->x1);
  RemoveNegativeZero(&quad->x2);
}

void SolveQuadratic(SquareEquation *quad) {
  assert(quad);
  double diskr = quad->b * quad->b - 4 * quad->a * quad->c;
  double sq_diskr = sqrt(diskr);
  if (ZeroComp(diskr) < 0) {
    quad->number_of_solutions = zero_solutions;
  } else if (ZeroComp(diskr) == 0) {
    quad->x1 = -quad->b / 2 / quad->a;
    quad->number_of_solutions = one_solution;
  } else {
    quad->x1 = (-quad->b - sq_diskr) / 2 / quad->a;
    quad->x2 = (-quad->b + sq_diskr) / 2 / quad->a;
    quad->number_of_solutions = two_solutions;
  }
}

void SolveLinear(SquareEquation *quad) {
  assert(quad);
  if (ZeroComp(quad->b) == 0) {
    if (ZeroComp(quad->c) == 0)
      quad->number_of_solutions = inf_solutions;
    else
      quad->number_of_solutions = zero_solutions;
  } else {
    quad->x1 = -quad->c / quad->b;
    quad->number_of_solutions = one_solution;
  }
}

PRINT_RESULTS_ERRORS PrintResult(SquareEquation quad) {
  switch (quad.number_of_solutions) {
    case zero_solutions: 
      printf("There is no solution for this square equation\n");
      break;
    case one_solution:
      printf("Solution has found: x = %lf\n", quad.x1);
      break;
    case two_solutions:
      printf("Solution has found: x1 = %lf, x2 = %lf\n", quad.x1, quad.x2);
      break;
    case inf_solutions:
      printf("Every possible x is allowed for this equation\n");
      break;
    case undefined_solutions:
    default:
      printf("Invalid arguments in PrintResult function: Undefined amount of solutions\n");
      return undefined_amount_of_solutions;
  }
  return no_print_results_errors;
}
