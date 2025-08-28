#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_input.hpp"

int ReadInput(SquareEquation *const quad, FILE *const input_fp) {
  assert(quad);
  assert(input_fp);

  if (fscanf(input_fp, "%lf%lf%lf", &quad->a, &quad->b, &quad->c) != 3) {
    fprintf(stderr, "Incorrect input data: Provided symbols is not a number\n");
    return 1;
  }
  if (!isfinite(quad->a) || !isfinite(quad->b) || !isfinite(quad->c)) {
    fprintf(stderr, "Incorrect input data: Provided number is not finite\n");
    return 1;
  }

  return 0;
}

int ParseInput(SquareEquation *const quad, FILE *const input_fp) {
  assert(quad);
  assert(input_fp);

  int ch = 0;
  int deg = 0, changed = 0, after_dot = 0, prev_mark = 1;
  double tmp = 0;
  double nums[3] = {0., 0., 0.};
  while ((ch = fgetc(input_fp)) != EOF) {
    if (isdigit(ch) && deg != 2 && !after_dot) {
      changed = 1;
      tmp = tmp * 10 + (ch - '0');
    } else if (isdigit(ch) && deg != 2 && after_dot) {
      changed = 1;
      tmp += (ch - '0') * pow(10, -after_dot);
      ++after_dot;
    } else if (ch == '.') {
      after_dot = 1;
    } else if (ch == 'x') {
      deg = 1;
    } else if (ch == '^') {
      deg = 2;
    } else if (ch == '+' || ch == '-' || ch == '\n' || ch == '@') {
      nums[deg] += (!changed && deg ? prev_mark : tmp * prev_mark);
      prev_mark = (ch == '+' ? 1 : -1);
      tmp = 0.;
      changed = deg = after_dot = 0;
      if (ch == '\n' || ch == '@')
        break;
    }
  }
  quad->c = nums[0];
  quad->b = nums[1];
  quad->a = nums[2];
  return 0;
}
