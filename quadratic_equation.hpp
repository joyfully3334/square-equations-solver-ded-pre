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
  double a = 0., b = 0., c = 0., x1 = 0., x2 = 0.;
  AMOUNT_OF_SOLUTIONS number_of_solutions = undefined_solutions;
};

#endif // QUADRATIC_EQUATION_HPP
