#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum INPUT_ERRORS { no_input_errors = 0, not_a_number = 1, not_finite = 2 };
enum AMOUNT_OF_SOLUTIONS {
  zero_solutions = 0,
  one_solution   = 1,
  two_solutions  = 2,
  inf_solutions  = 3,
};
const double EPS = 1e-5;

enum INPUT_ERRORS ReadCoef(double *coef, char name);

enum INPUT_ERRORS ReadInput(struct SquareEquation *quad);

int CoefErrHandler(enum INPUT_ERRORS read_result);

int ZeroComp(double num);

void SolveQuadratic(struct SquareEquation *quad);

void PrintResult(struct SquareEquation quad);

struct SquareEquation {
  double a, b, c, x1, x2;
  enum AMOUNT_OF_SOLUTIONS number_of_solutions;
};

int main() {
  struct SquareEquation quad1 = {0., 0., 0., 0., 0., zero_solutions};
  if (CoefErrHandler(ReadInput(&quad1)))
    return 1;

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", quad1.a,
         (quad1.b >= 0 ? '+' : '-'), fabs(quad1.b),
         (quad1.c >= 0 ? '+' : '-'), fabs(quad1.c));

  SolveQuadratic(&quad1);
  PrintResult(quad1);

  return 0;
}

enum INPUT_ERRORS ReadCoef(double *coef, char name) {
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;
  return no_input_errors;
}

enum INPUT_ERRORS ReadInput(struct SquareEquation *quad) {
  enum INPUT_ERRORS ret_val = ReadCoef(&quad->a, 'a');
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

int CoefErrHandler(enum INPUT_ERRORS read_result) {
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


void SolveQuadratic(struct SquareEquation *quad) {
  double diskr = quad->b * quad->b - 4 * quad->a * quad->c;
  double sq_diskr = sqrt(diskr);
  if (ZeroComp(quad->a) == 0) {
    if (ZeroComp(quad->b) == 0) {
      if (ZeroComp(quad->c) == 0)
        quad->number_of_solutions = inf_solutions;
      else
        quad->number_of_solutions = zero_solutions;
    } else {
      quad->x1 = -quad->c / quad->b;
      quad->number_of_solutions = one_solution;
    }
  } else if (ZeroComp(diskr) < 0) {
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

void PrintResult(struct SquareEquation quad) {
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
    default:
      break;
  }
}
