#ifndef QUADRATIC_INPUT_HPP
#define QUADRATIC_INPUT_HPP

#include <stdio.h>

#include "quadratic_equation.hpp"

enum INPUT_ERRORS {
  no_input_errors = 0,
  not_a_number    = 1,
  not_finite      = 2
};

INPUT_ERRORS ReadCoef(double *const coef, const char name);

INPUT_ERRORS ReadInput(SquareEquation *const quad, FILE *input_fp);

INPUT_ERRORS ParseInput(SquareEquation *const quad, FILE *input_fp);

int InputErrorHandler(const INPUT_ERRORS read_result);

#endif // QUADRATIC_INPUT_HPP
