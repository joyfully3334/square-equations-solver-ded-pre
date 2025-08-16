#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum INPUT_ERRORS { not_a_number = 1, not_finite = 2 };
enum AMOUNT_OF_SOLUTIONS {
  zero_solutions = 0,
  one_solution = 1,
  two_solutions = 2,
  inf_solutions = 3
};
const double EPS = 1e-5;

int input_coef(double *coef, char name);

int read_coef(double *a, double *b, double *c);

int coef_err_handler(int read_result);

int zero_comp(double num);

int less_then_zero(double num);

void solve_quadratic(double a, double b, double c, double *x1, double *x2,
                     int *solutions);

void print_result(double x1, double x2, int solutions);

struct quadratic {
  double a, b, c, x1, x2;
  int solutions;
};

int main() {
  struct quadratic quad1 = {0., 0., 0., 0., 0., 0};
  if (coef_err_handler(read_coef(&quad1.a, &quad1.b, &quad1.c)))
    return 1;

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", quad1.a,
         (quad1.b >= 0 ? '+' : '-'), fabs(quad1.b), (quad1.c >= 0 ? '+' : '-'),
         fabs(quad1.c));

  solve_quadratic(quad1.a, quad1.b, quad1.c, &quad1.x1, &quad1.x2,
                  &quad1.solutions);
  print_result(quad1.x1, quad1.x2, quad1.solutions);

  return 0;
}

int input_coef(double *coef, char name) {
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;
  return 0;
}

int read_coef(double *a, double *b, double *c) {
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
  *c = nums[0];
  *b = nums[1];
  *a = nums[2];
  return 0;
}

int coef_err_handler(int read_result) {
  if (read_result == not_a_number) {
    printf("Incorrect input data: Provided symbols is not a number\n");
    return 1;
  } else if (read_result == not_finite) {
    printf("Incorrect input data: Provided number is not finite\n");
    return 1;
  }
  return 0;
}

int zero_comp(double num) { return (fabs(num - 0.) <= EPS); }

int less_then_zero(double num) { return (num < -EPS); }

void solve_quadratic(double a, double b, double c, double *x1, double *x2,
                     int *solutions) {
  double diskr = b * b - 4 * a * c;
  double sq_diskr = sqrt(diskr);
  if (zero_comp(a)) {
    if (zero_comp(b)) {
      if (zero_comp(b))
        *solutions = inf_solutions;
      else
        *solutions = zero_solutions;
    } else {
      *x1 = -(double)c / b;
      *solutions = one_solution;
    }
  } else if (less_then_zero(diskr)) {
    *solutions = zero_solutions;
  } else if (zero_comp(diskr)) {
    *x1 = -(double)b / 2 / a;
    *solutions = one_solution;
  } else {
    *x1 = (-b - sq_diskr) / 2 / a;
    *x2 = (-b + sq_diskr) / 2 / a;
    *solutions = two_solutions;
  }
}

void print_result(double x1, double x2, int solutions) {
  if (solutions == zero_solutions)
    printf("There is no solution for this square equation\n");
  else if (solutions == one_solution)
    printf("Solution has found: x = %lf\n", x1);
  else if (solutions == two_solutions)
    printf("Solution has found: x1 = %lf, x2 = %lf\n", x1, x2);
  else if (solutions == inf_solutions)
    printf("Every possible x is allowed for this equation\n");
}
