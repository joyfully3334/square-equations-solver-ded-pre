#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
  int a, b, c;
  fputs("Enter a: ", stdout);
  scanf("%d", &a);
  fputs("Enter b: ", stdout);
  scanf("%d", &b);
  fputs("Enter c: ", stdout);
  scanf("%d", &c);

  printf("Solving equation: %dx^2 %c %dx %c %d = 0\n", a,
         (b >= 0 ? '+' : '-'), abs(b),
         (c >= 0 ? '+' : '-'), abs(c));

  int diskr = b * b - 4 * a * c;
  if (diskr < 0) {
    printf("There is no solution for this square equation\n");
  } else if (diskr == 0) {
    double x = -(double)b / 2 / a;
    printf("Solution has found: x = %f\n", x);
  } else {
    double x1 = (double)(-b - sqrt(diskr)) / 2 / a;
    double x2 = (double)(-b + sqrt(diskr)) / 2 / a;
    printf("Solution has found: x1 = %f, x2 = %f\n", x1, x2);
  }

  return 0;
}
