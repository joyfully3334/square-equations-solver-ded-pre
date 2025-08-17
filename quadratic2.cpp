#include <assert.h>
#include <ctype.h>
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

struct SquareEquation {
  double a, b, c, x1, x2;
  AMOUNT_OF_SOLUTIONS number_of_solutions;
};

INPUT_ERRORS ReadCoef(double *coef, char name);

INPUT_ERRORS ReadInput(SquareEquation *quad);

int CoefErrHandler(INPUT_ERRORS read_result);

int ZeroComp(double num);

void SolveEquation(SquareEquation *quad);

void SolveQuadratic(SquareEquation *quad);

void SolveLinear(SquareEquation *quad);

int PrintResult(SquareEquation quad);

int main() {
  SquareEquation quad1 = {0., 0., 0., 0., 0., zero_solutions};
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
  assert(coef != NULL);
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;
  return no_input_errors;
}

INPUT_ERRORS ReadInput(SquareEquation *quad) {
  const int MAX_LEN = 81;
  char input[MAX_LEN];
  printf("Enter square equation (format: ax^2 + bx + c): ");
  fgets(input, MAX_LEN, stdin);
  double tmp = 0;
  int deg = 0, changed = 0, after_dot = 0, prev_mark = 1;
  double nums[3] = {0., 0., 0.};
  for (int i = 0; i < MAX_LEN; ++i) {
    if (isdigit(input[i]) && deg != 2 && !after_dot) {
      changed = 1;
      tmp = tmp * 10 + (input[i] - '0');
    } else if (isdigit(input[i]) && deg != 2 && after_dot) {
      changed = 1;
      tmp += (input[i] - '0') * pow(10, -after_dot);
      ++after_dot;
    } else if (input[i] == '.') {
      after_dot = 1;
    } else if (input[i] == 'x') {
      deg = 1;
    } else if (input[i] == '^') {
      deg = 2;
    } else if (input[i] == '+' || input[i] == '-' || input[i] == '\0') {
      nums[deg] += (!changed && deg ? prev_mark : tmp * prev_mark);
      prev_mark = (input[i] == '+' ? 1 : -1);
      tmp = 0.;
      deg = after_dot = 0;
      if (input[i] == '\0')
        break;
    }
  }
  quad->c = nums[0];
  quad->b = nums[1];
  quad->a = nums[2];
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


void SolveEquation(SquareEquation *quad) {
  assert(quad != NULL);
  if (ZeroComp(quad->a) == 0)
    SolveLinear(quad);
  else
    SolveQuadratic(quad);
}

void SolveQuadratic(SquareEquation *quad) {
  assert(quad != NULL);
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
  assert(quad != NULL);
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

int PrintResult(SquareEquation quad) {
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
      printf("An error occured in PrintResult function");
      return 1;
  }
  return 0;
}
