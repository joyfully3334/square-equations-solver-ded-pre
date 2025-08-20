#include <assert.h>
#include <math.h>
#include <stdio.h>
#include "quadratic_input.hpp"

INPUT_ERRORS ReadCoef(double *coef, const char name) {
  assert(coef);
  printf("Enter %c: ", name);
  if (!scanf("%lf", coef))
    return not_a_number;
  if (!isfinite(*coef))
    return not_finite;
  return no_input_errors;
}

INPUT_ERRORS ReadInput(SquareEquation *quad) {
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

int InputErrorHandler(const INPUT_ERRORS read_result) {
  if (read_result == not_a_number) {
    printf("Incorrect input data: Provided symbols is not a number\n");
    return 1;
  } else if (read_result == not_finite) {
    printf("Incorrect input data: Provided number is not finite\n");
    return 1;
  }
  return 0;
}
