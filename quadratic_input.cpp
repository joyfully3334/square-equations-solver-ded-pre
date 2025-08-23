#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_input.hpp"

INPUT_ERRORS ReadCoef(double *const coef, const char name) {
  assert(coef);

  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;

  return no_input_errors;
}

INPUT_ERRORS ReadInput(SquareEquation *const quad) {
  assert(quad);

  INPUT_ERRORS ret_val = ReadCoef(&quad->a, 'a');
  if (ret_val)
    return ret_val;
  ret_val = ReadCoef(&quad->b, 'b');
  if (ret_val)
    return ret_val;
  ret_val = ReadCoef(&quad->c, 'c');
  if (ret_val)
    return ret_val;

  return no_input_errors;
}

INPUT_ERRORS ParseInput(SquareEquation *const quad) {
  assert(quad);

  const int MAX_LEN = 81;
  char input[MAX_LEN] = {};
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
      changed = deg = after_dot = 0;
      if (input[i] == '\0')
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
