#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 81

void read_coef(int *a, int *b, int *c);

int main() {
  int a, b, c;
  read_coef(&a, &b, &c);

  printf("Solving equation: %dx^2 %c %dx %c %d = 0\n", a,
         (b >= 0 ? '+' : '-'), abs(b),
         (c >= 0 ? '+' : '-'), abs(c));

  int diskr = b * b - 4 * a * c;
  int sq_diskr = sqrt(diskr);
  if (a == 0) {
    if (b == 0) {
      if (c == 0)
        printf("Every possible x is allowed for this equation\n");
      else
        printf("There is no solution for this equation\n");
    } else {
      double x = -(double)c / b;
      printf("Solution has found: x = %f\n", x);
    }
  } else if (diskr < 0) {
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
}
