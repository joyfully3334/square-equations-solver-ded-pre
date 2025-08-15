#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int input_coef(double *coef, char name);

void zero_comp(double num, const double EPS);

int main() {
  const double EPS = 1e-5;
  double a = 0., b = 0., c = 0.;
  if (input_coef(&a, 'a')) {
    fputs("ERROR: Incorrect input data", stdout);
    exit(EXIT_FAILURE);
  }
  if (input_coef(&b, 'b')) {
    fputs("ERROR: Incorrect input data", stdout);
    exit(EXIT_FAILURE);
  }
  if (input_coef(&c, 'c')) {
    fputs("ERROR: Incorrect input data", stdout);
    exit(EXIT_FAILURE);
  }

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", a,
         (b >= 0 ? '+' : '-'), fabs(b),
         (c >= 0 ? '+' : '-'), fabs(c));

  double diskr = b * b - 4 * a * c;
  double sq_diskr = sqrt(diskr);
  if (fabs(a - 0) <= EPS) {
    if (fabs(b - 0) <= EPS) {
      if (fabs(c - 0) <= EPS)
        printf("Every possible x is allowed for this equation\n");
      else
        printf("There is no solution for this equation\n");
    } else {
      double x = -(double)c / b;
      printf("Solution has found: x = %lf\n", x);
    }
  } else if (diskr < -EPS) {
    printf("There is no solution for this square equation\n");
  } else if (fabs(diskr - 0) <= EPS) {
    double x = -(double)b / 2 / a;
    printf("Solution has found: x = %lf\n", x);
  } else {
    double x1 = (-b - sq_diskr) / 2 / a;
    double x2 = (-b + sq_diskr) / 2 / a;
    printf("Solution has found: x1 = %lf, x2 = %lf\n", x1, x2);
  }

  return 0;
}

int input_coef(double *coef, char name) {
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef)) {
    return 1;
  }
  return 0;
}
