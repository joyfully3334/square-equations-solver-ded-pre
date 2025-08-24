#ifndef QUADRATIC_PRINT_HPP
#define QUADRATIC_PRINT_HPP

#include "quadratic_equation.hpp"

enum PRINT_RESULTS_ERRORS {
  no_print_results_errors       = 0,
  undefined_amount_of_solutions = 1,
};

PRINT_RESULTS_ERRORS PrintResult(const SquareEquation quad);

void PrintWelcome();

void PrintHelp();

void PrintTestError(SquareEquation *const quads, const int i, const char *const tests_filename);

void PrintTestSuccess();

#endif // QUADRATIC_PRINT_HPP
