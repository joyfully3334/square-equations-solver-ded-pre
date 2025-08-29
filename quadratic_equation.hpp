//--------------------------------------------------------------
//! @file quadratic_equation.hpp
//!
//! Contains SquareEquation structure
//--------------------------------------------------------------

#ifndef QUADRATIC_EQUATION_HPP
#define QUADRATIC_EQUATION_HPP

enum AMOUNT_OF_SOLUTIONS {
  undefined_solutions = -1,
  zero_solutions      =  0,
  one_solution        =  1,
  two_solutions       =  2,
  inf_solutions       =  3,
};

//--------------------------------------------------------------
//! Main structure of this programm.
//!
//! Presents square equation with its parameters and solutions.
//!
//! @param a                   Coefficient of second degree
//! @param b                   Coefficient of first degree
//! @param c                   Free coefficient
//! @param x1                  First answer
//! @param x2                  Second answer
//! @param number_of_solutions Amount of solutions
//!
//! @see SolveEquation PrintResult
//---------------------------------------------------------------

struct SquareEquation {
  double a, b, c, x1, x2;
  AMOUNT_OF_SOLUTIONS number_of_solutions;
};

#endif // QUADRATIC_EQUATION_HPP
