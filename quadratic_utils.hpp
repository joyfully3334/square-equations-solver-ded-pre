//--------------------------------------------------------------
//! @file quadratic_utils.hpp
//!
//! Contains extra functions
//--------------------------------------------------------------

#ifndef QUADRATIC_UTILS_HPP
#define QUADRATIC_UTILS_HPP

#include "quadratic_equation.hpp"

//--------------------------------------------------------------
//! Compares numbers of type double
//!
//! Default accuracy is 1e-5
//!
//! @param [in] num1 First number
//! @param [in] num2 Second number
//!
//! @return Positive value if num1 > num2, Negative if num1 < num2, else 0
//--------------------------------------------------------------

int DoubleComp(const double num1, const double num2);

//--------------------------------------------------------------
//! Checks if num equals -0 and converts to 0 if it is
//!
//! @param [out] num Number of type double to be changed
//--------------------------------------------------------------

void RemoveNegativeZero(double *const num);

//--------------------------------------------------------------
//! Checks if flag is in the argv
//!
//! @param [int] argc Amount of arguments
//! @param [int] argv All arguments
//! @param [int] flag Flag that function tries to find
//!
//! @return Positive value if flag found, else 0
//--------------------------------------------------------------

int CheckFlag(int argc, char **argv, const char *const flag);

//--------------------------------------------------------------
//! Compares solutions of two structes of type SquareEquation
//!
//! @param [int] quad1 First struct
//! @param [int] quad2 Second struct
//!
//! @return Positive value if solutions differs, else 0
//--------------------------------------------------------------

int QuadraticComp(const SquareEquation quad1, const SquareEquation quad2);

//--------------------------------------------------------------
//! Reads amount of lines from file
//!
//! @param [int] filename Name of file to read from
//!
//! @return Amount of lines in file
//--------------------------------------------------------------

int GetAmountOfLines(const char *const filename);

#endif // QUADRATIC_UTILS_HPP
