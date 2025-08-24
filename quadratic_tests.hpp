#ifndef QUADRATIC_TESTS_HPP
#define QUADRATIC_TESTS_HPP

#include "quadratic_equation.hpp"

int ReadTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]);

int ParseTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]);

int RunTest(SquareEquation *const quad);

int ExecuteTests();

#endif // QUADRATIC_TESTS_HPP
