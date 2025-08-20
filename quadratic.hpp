#ifndef QUADRATIC_IMPORTED
#define QUADRATIC_IMPORTED

enum AMOUNT_OF_SOLUTIONS {
  undefined_solutions = -1,
  zero_solutions      =  0,
  one_solution        =  1,
  two_solutions       =  2,
  inf_solutions       =  3,
};

struct SquareEquation {
  double a, b, c, x1, x2;
  AMOUNT_OF_SOLUTIONS number_of_solutions;
};

void SolveEquation(SquareEquation *quad);

enum PRINT_RESULTS_ERRORS {
  no_print_results_errors       = 0,
  undefined_amount_of_solutions = 1,
};
const double EPS = 1e-5;

PRINT_RESULTS_ERRORS PrintResult(const SquareEquation quad);

#endif
