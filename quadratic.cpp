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

enum INPUT_ERRORS Read_Coef(double *coef, char name);

enum INPUT_ERRORS Read_Input(struct SquareEquation *quad);

int Coef_Err_Handler(enum INPUT_ERRORS read_result);

int Zero_Comp(double num);

int Less_Then_Zero(double num);

void Solve_Quadratic(struct SquareEquation *quad);

void Print_Result(struct SquareEquation quad);

struct SquareEquation {
  double a, b, c, x1, x2;
  enum AMOUNT_OF_SOLUTIONS number_of_solutions;
};

int main() {
  struct SquareEquation quad1 = {0., 0., 0., 0., 0., zero_solutions};
  if (Coef_Err_Handler(Read_Input(&quad1)))
    return 1;

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", quad1.a,
         (quad1.b >= 0 ? '+' : '-'), fabs(quad1.b),
         (quad1.c >= 0 ? '+' : '-'), fabs(quad1.c));

  Solve_Quadratic(&quad1);
  Print_Result(quad1);

  return 0;
}

enum INPUT_ERRORS Read_Coef(double *coef, char name) {
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;
  return no_input_errors;
}

INPUT_ERRORS Read_Input(struct SquareEquation *quad) {
  enum INPUT_ERRORS ret_val = Read_Coef(&quad->a, 'a');
  if (ret_val)
    return ret_val;
  ret_val = Read_Coef(&quad->b, 'b');
  if (ret_val)
    return ret_val;
  ret_val = Read_Coef(&quad->c, 'c');
  if (ret_val)
    return ret_val;
  return no_input_errors;
}

int Coef_Err_Handler(enum INPUT_ERRORS read_result) {
  if (read_result == not_a_number) {
    printf("Incorrect input data: Provided symbols is not a number\n");
    return 1;
  } else if (read_result == not_finite) {
    printf("Incorrect input data: Provided number is not finite\n");
    return 1;
  }
  return 0;
}

int Zero_Comp(double num) { return (fabs(num - 0.) <= EPS); }

int Less_Then_Zero(double num) { return (num < -EPS); }

void Solve_Quadratic(struct SquareEquation *quad) {
  double diskr = quad->b * quad->b - 4 * quad->a * quad->c;
  double sq_diskr = sqrt(diskr);
  if (Zero_Comp(quad->a)) {
    if (Zero_Comp(quad->b)) {
      if (Zero_Comp(quad->c))
        quad->number_of_solutions = inf_solutions;
      else
        quad->number_of_solutions = zero_solutions;
    } else {
      quad->x1 = -(double)quad->c / quad->b;
      quad->number_of_solutions = one_solution;
    }
  } else if (Less_Then_Zero(diskr)) {
    quad->number_of_solutions = zero_solutions;
  } else if (Zero_Comp(diskr)) {
    quad->x1 = -(double)quad->b / 2 / quad->a;
    quad->number_of_solutions = one_solution;
  } else {
    quad->x1 = (-quad->b - sq_diskr) / 2 / quad->a;
    quad->x2 = (-quad->b + sq_diskr) / 2 / quad->a;
    quad->number_of_solutions = two_solutions;
  }
}

void Print_Result(struct SquareEquation quad) {
  if (quad.number_of_solutions == zero_solutions)
    printf("There is no solution for this square equation\n");
  else if (quad.number_of_solutions == one_solution)
    printf("Solution has found: x = %lf\n", quad.x1);
  else if (quad.number_of_solutions == two_solutions)
    printf("Solution has found: x1 = %lf, x2 = %lf\n", quad.x1, quad.x2);
  else if (quad.number_of_solutions == inf_solutions)
    printf("Every possible x is allowed for this equation\n");
}
