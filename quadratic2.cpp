#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int input_coef(double *coef, char name);

int zero_comp(double num, const double EPS);

int read_coef(double *a, double *b, double *c);

int main() {
  const double EPS = 1e-5;
  double a = 0., b = 0., c = 0.;
  if (read_coef(&a, &b, &c)) {
    printf("ERROR: Incorrect input data\n");
    exit(EXIT_FAILURE);
  }

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", a,
         (b >= 0 ? '+' : '-'), fabs(b),
         (c >= 0 ? '+' : '-'), fabs(c));

  double diskr = b * b - 4 * a * c;
  double sq_diskr = sqrt(diskr);
  if (zero_comp(a, EPS)) {
    if (zero_comp(b, EPS)) {
      if (zero_comp(b, EPS))
        printf("Every possible x is allowed for this equation\n");
      else
        printf("There is no solution for this equation\n");
    } else {
      double x = -(double)c / b;
      printf("Solution has found: x = %lf\n", x);
    }
  } else if (diskr < -EPS) {
    printf("There is no solution for this square equation\n");
  } else if (zero_comp(diskr, EPS)) {
    double x = -(double)b / 2 / a;
    printf("Solution has found: x = %lf\n", x);
  } else {
    double x1 = (-b - sq_diskr) / 2 / a;
    double x2 = (-b + sq_diskr) / 2 / a;
    printf("Solution has found: x1 = %lf, x2 = %lf\n", x1, x2);
  }

  return 0;
}

int zero_comp(double num, const double EPS) {
  return (fabs(num - 0.) <= EPS);
}

int input_coef(double *coef, char name) {
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef) || !isfinite(*coef)) {
    return 1;
  }
  return 0;
}

int read_coef(double *a, double *b, double *c) {
  const int MAX_LEN = 81;
  char input[MAX_LEN];
  fputs("Enter square equation (format: ax^2 + bx + c): ", stdout);
  fgets(input, MAX_LEN, stdin);
  int tmp = 0, deg = 0, prev_mark = 1, changed = 0;
  int nums[3] = {0, 0, 0};
  for (int i = 0; i < MAX_LEN; ++i) {
    if (isdigit(input[i]) && deg != 2) {
      changed = 1;
      tmp = tmp * 10 + (input[i] - '0');
    } else if (input[i] == 'x') {
      deg = 1;
    } else if (input[i] == '^') {
      deg = 2;
    } else if (input[i] == '+' || input[i] == '-' || input[i] == '\0') {
      nums[deg] += (!changed && deg ? 1 : tmp * prev_mark);
      prev_mark = (input[i] == '+' ? 1 : -1);
      tmp = deg = 0;
      if (input[i] == '\0')
        break;
    }
  }
  *c = nums[0];
  *b = nums[1];
  *a = nums[2];
  return 0;
}
