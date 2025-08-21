#ifndef QUADRATIC_INPUT_HPP
#define QUADRATIC_INPUT_HPP

#include "quadratic_equation.hpp"

enum INPUT_ERRORS {
  no_input_errors = 0,
  not_a_number    = 1,
  not_finite      = 2
};

INPUT_ERRORS ReadCoef(double *coef, const char name);

INPUT_ERRORS ReadInput(SquareEquation *quad);

int InputErrorHandler(const INPUT_ERRORS read_result);

#endif // QUADRATIC_INPUT_HPP
