#ifndef QUADRATIC_EQUATION_HPP
#define QUADRATIC_EQUATION_HPP

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

#endif // QUADRATIC_EQUATION_HPP
