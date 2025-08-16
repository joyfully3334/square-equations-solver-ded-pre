#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double EPS = 1e-5;

int input_coef(double *coef, char name);

int read_coef(double *a, double *b, double *c);

void coef_err_handler(int read_result);

int zero_comp(double num);

void solve_quadratic(double a, double b, double c, double *x1, double *x2);

void print_result(double x1, double x2);

int main() {
  double a = 0., b = 0., c = 0.;
  coef_err_handler(read_coef(&a, &b, &c));

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

void coef_err_handler(int read_result) {
  if (read_result == 1) {
    printf("Incorrect input data: Provided symbols is not a number\n");
    exit(EXIT_FAILURE);
  } else if (read_result == 2) {
    printf("Incorrect input data: Provided number is not finite\n");
    exit(EXIT_FAILURE);
  }
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
