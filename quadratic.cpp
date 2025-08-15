#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
  double a = 0., b = 0., c = 0.;
  fputs("Enter a: ", stdout);
  scanf("%lf", &a);
  fputs("Enter b: ", stdout);
  scanf("%lf", &b);
  fputs("Enter c: ", stdout);
  scanf("%lf", &c);

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", a,
         (b >= 0 ? '+' : '-'), abs(b),
         (c >= 0 ? '+' : '-'), abs(c));

  int diskr = b * b - 4 * a * c;
  double sq_diskr = sqrt(diskr);
  if (a == 0) {
    if (b == 0) {
      if (c == 0)
        printf("Every possible x is allowed for this equation\n");
      else
        printf("There is no solution for this equation\n");
    } else {
      double x = -(double)c / b;
      printf("Solution has found: x = %lf\n", x);
    }
  } else if (diskr < 0) {
    printf("There is no solution for this square equation\n");
  } else if (diskr == 0) {
    double x = -(double)b / 2 / a;
    printf("Solution has found: x = %lf\n", x);
  } else {
    double x1 = (-b - sq_diskr) / 2 / a;
    double x2 = (-b + sq_diskr) / 2 / a;
    printf("Solution has found: x1 = %lf, x2 = %lf\n", x1, x2);
  }

  return 0;
}
