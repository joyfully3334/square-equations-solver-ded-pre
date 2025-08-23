#ifndef QUADRATIC_TESTS_HPP
#define QUADRATIC_TESTS_HPP

#include "quadratic_equation.hpp"

int ReadTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]);

int ParseTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]);

int RunStandardTest(SquareEquation *const quad);

int ExecuteProgrammWithTesting();

#endif // QUADRATIC_TESTS_HPP
