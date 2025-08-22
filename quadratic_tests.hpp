#ifndef QUADRATIC_TESTS_HPP
#define QUADRATIC_TESTS_HPP

#include "quadratic_equation.hpp"

int ReadTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]);

int ExecuteProgrammTest(SquareEquation *const quad);

int ExecuteProgrammWithTesting(const char *const filename);

#endif // QUADRATIC_TESTS_HPP
