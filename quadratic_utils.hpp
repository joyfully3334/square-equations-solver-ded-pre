#ifndef QUADRATIC_UTILS_HPP
#define QUADRATIC_UTILS_HPP

#include "quadratic_equation.hpp"

int DoubleComp(const double num1, const double num2);

void RemoveNegativeZero(double *const num);

int ReadTests(const char *const  filename, const int MAX_SIZE, SquareEquation quads[]);

#endif // QUADRATIC_UTILS_HPP
