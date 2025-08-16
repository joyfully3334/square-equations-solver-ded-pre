#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double EPS = 1e-5;

int input_coef(double *coef, char name);

int read_coef(double *a, double *b, double *c);

int coef_err_handler(int read_result);

int zero_comp(double num);

void solve_quadratic(double a, double b, double c, double *x1, double *x2);

void print_result(double x1, double x2);

int main() {
  double a = 0., b = 0., c = 0.;
  if (coef_err_handler(read_coef(&a, &b, &c)))
    return 1;

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", a,
         (b >= 0 ? '+' : '-'), fabs(b),
         (c >= 0 ? '+' : '-'), fabs(c));

  double x1 = 0., x2 = 0.;
  solve_quadratic(a, b, c, &x1, &x2);

  print_result(x1, x2);

  return 0;
}

int input_coef(double *coef, char name) {
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return 1;
  if (!isfinite(*coef))
    return 2;
  return 0;
}

int read_coef(double *a, double *b, double *c) {
  int ret_val = input_coef(a, 'a');
  if (ret_val)
    return ret_val;
  ret_val = input_coef(b, 'b');
  if (ret_val)
    return ret_val;
  ret_val = input_coef(c, 'c');
  if (ret_val)
    return ret_val;
  return 0;
}

int coef_err_handler(int read_result) {
  if (read_result == 1) {
    printf("Incorrect input data: Provided symbols is not a number\n");
    return 1;
  } else if (read_result == 2) {
    printf("Incorrect input data: Provided number is not finite\n");
    return 1;
  }
  return 0;
}

int zero_comp(double num) { return (fabs(num - 0.) <= EPS); }

void solve_quadratic(double a, double b, double c, double *x1, double *x2) {
  double diskr = b * b - 4 * a * c;
  double sq_diskr = sqrt(diskr);
  if (zero_comp(a)) {
    if (zero_comp(b)) {
      if (zero_comp(b))
        *x1 = *x2 = INFINITY;
      else
        *x1 = *x2 = NAN;
    } else {
      *x1 = -(double)c / b;
      *x2 = NAN;
    }
  } else if (diskr < -EPS) {
    *x1 = *x2 = NAN;
  } else if (zero_comp(diskr)) {
    *x1 = -(double)b / 2 / a;
    *x2 = NAN;
  } else {
    *x1 = (-b - sq_diskr) / 2 / a;
    *x2 = (-b + sq_diskr) / 2 / a;
  }
}

void print_result(double x1, double x2) {
  if (isnan(x1) && isnan(x2))
    printf("There is no solution for this square equation\n");
  else if (isinf(x1) && isinf(x2))
    printf("Every possible x is allowed for this equation\n");
  else if (isnan(x2))
    printf("Solution has found: x = %lf\n", x1);
  else
    printf("Solution has found: x1 = %lf, x2 = %lf\n", x1, x2);
}
