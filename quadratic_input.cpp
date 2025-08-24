#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_input.hpp"

INPUT_ERRORS ReadCoef(double *const coef, FILE *input_fp) {
  assert(coef);

  if (!fscanf(input_fp, "%lg", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;

  return no_input_errors;
}

INPUT_ERRORS ReadInput(SquareEquation *const quad, FILE *input_fp) {
  assert(quad);

  INPUT_ERRORS ret_val = ReadCoef(&quad->a, input_fp);
  if (ret_val)
    return ret_val;
  ret_val = ReadCoef(&quad->b, input_fp);
  if (ret_val)
    return ret_val;
  ret_val = ReadCoef(&quad->c, input_fp);
  if (ret_val)
    return ret_val;

  return no_input_errors;
}

INPUT_ERRORS ParseInput(SquareEquation *const quad, FILE *input_fp) {
  assert(quad);
  assert(input_fp);

  int ch = 0;
  double tmp = 0;
  int deg = 0, changed = 0, after_dot = 0, prev_mark = 1;
  double nums[3] = {0., 0., 0.};
  for (int i = 0; (ch = fgetc(input_fp)) != EOF; ++i) {
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
    } else if (ch == '+' || ch == '-' || ch == '\n') {
      nums[deg] += (!changed && deg ? prev_mark : tmp * prev_mark);
      prev_mark = (ch == '+' ? 1 : -1);
      tmp = 0.;
      changed = deg = after_dot = 0;
      if (ch == '\n')
        break;
    }
  }
  quad->c = nums[0];
  quad->b = nums[1];
  quad->a = nums[2];
  return no_input_errors;
}

int InputErrorHandler(const INPUT_ERRORS read_result) {
  if (read_result == not_a_number) {
    fprintf(stderr, "Incorrect input data: Provided symbols is not a number\n");
    return 1;
  } else if (read_result == not_finite) {
    fprintf(stderr, "Incorrect input data: Provided number is not finite\n");
    return 1;
  }

  return 0;
}
