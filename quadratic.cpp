#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double EPS = 1e-5;

int input_coef(double *coef, char name);

int zero_comp(double num);

int read_coef(double *a, double *b, double *c);

int main() {
  double a = 0., b = 0., c = 0.;
  if (read_coef(&a, &b, &c)) {
    printf("ERROR: Incorrect input data\n");
    return 1;
  }

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", a,
         (b >= 0 ? '+' : '-'), fabs(b),
         (c >= 0 ? '+' : '-'), fabs(c));

  double diskr = b * b - 4 * a * c;
  double sq_diskr = sqrt(diskr);
  if (zero_comp(a)) {
    if (zero_comp(b)) {
      if (zero_comp(b))
        printf("Every possible x is allowed for this equation\n");
      else
        printf("There is no solution for this equation\n");
    } else {
      double x = -(double)c / b;
      printf("Solution has found: x = %lf\n", x);
    }
  } else if (diskr < -EPS) {
    printf("There is no solution for this square equation\n");
  } else if (zero_comp(diskr)) {
    double x = -(double)b / 2 / a;
    printf("Solution has found: x = %lf\n", x);
  } else {
    double x1 = (-b - sq_diskr) / 2 / a;
    double x2 = (-b + sq_diskr) / 2 / a;
    printf("Solution has found: x1 = %lf, x2 = %lf\n", x1, x2);
  }

  return 0;
}

int zero_comp(double num) {
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
  int ret_val = 0;
  ret_val += input_coef(a, 'a');
  ret_val += input_coef(b, 'b');
  ret_val += input_coef(c, 'c');
  return ret_val;
}
