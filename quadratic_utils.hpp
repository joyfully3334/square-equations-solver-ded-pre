#ifndef QUADRATIC_UTILS_HPP
#define QUADRATIC_UTILS_HPP

#include "quadratic_equation.hpp"

int DoubleComp(const double num1, const double num2);

void RemoveNegativeZero(double *const num);

int CheckFlag(int argc, char **argv, const char *flag);

int QuadraticComp(const SquareEquation quad1, const SquareEquation quad2);

#endif // QUADRATIC_UTILS_HPP
