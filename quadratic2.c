#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void read_coef(int *a, int *b, int *c);

int main() {
  int a, b, c;
  read_coef(&a, &b, &c);

  printf("Solving equation: %dx^2 %c %dx %c %d = 0\n", a,
         (b > 0 ? '+' : '-'), abs(b),
         (c > 0 ? '+' : '-'), abs(c));

  int diskr = b * b - 4 * a * c;
  int sq_diskr = sqrt(diskr);
  if (diskr < 0) {
    printf("There is no solution for this square equation\n");
  } else if (diskr == 0) {
    double x = -(double)b / 2 / a;
    printf("Solution has found: x = %f\n", x);
  } else {
    double x1 = (double)(-b - sq_diskr) / 2 / a;
    double x2 = (double)(-b + sq_diskr) / 2 / a;
    printf("Solution has found: x1 = %f, x2 = %f\n", x1, x2);
  }

  return 0;
}

void read_coef(int *a, int *b, int *c) {
  int max_len = 50;
  char input[max_len];
  fputs("Enter square equation (format: ax^2 + bx + c): ", stdout);
  fgets(input, max_len, stdin);
  int cur = 0, mark = 1;
  int nums[3] = {0, 0, 0};
  for (int i = 0; i < max_len; ++i) {
    if (isdigit(input[i]) && (i <= 0 || input[i - 1] != '^')) {
      nums[cur] = nums[cur] * 10 + (input[i] - '0') * mark;
    } else if (input[i] == 'x') {
      ++cur;
      mark = 0;
    } else if (input[i] == '+') {
      mark = 1;
    } else if (input[i] == '-') {
      mark = -1;
    }
  }
  *a = nums[0];
  *b = nums[1];
  *c = nums[2];
}
