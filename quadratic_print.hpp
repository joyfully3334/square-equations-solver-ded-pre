//--------------------------------------------------------------
//! @file quadratic_print.hpp
//!
//! Contains print functions
//--------------------------------------------------------------

#ifndef QUADRATIC_PRINT_HPP
#define QUADRATIC_PRINT_HPP

#include "quadratic_equation.hpp"

enum PRINT_RESULTS_ERRORS {
  no_print_results_errors       = 0,
  undefined_amount_of_solutions = 1,
};

//--------------------------------------------------------------
//! Prints result of square equation
//!
//! @param [in] quad Structure of type SquareEquation
//!
//! @see SquareEquation
//--------------------------------------------------------------

PRINT_RESULTS_ERRORS PrintResult(const SquareEquation quad);

//--------------------------------------------------------------
//! Prints welcome message
//!
//! @note Must be used only when --silent flag **is not** set
//--------------------------------------------------------------

void PrintWelcome();

//--------------------------------------------------------------
//! Prints help message
//!
//! @note Must be used only when --help flag **is** set
//--------------------------------------------------------------

void PrintHelp();

//--------------------------------------------------------------
//! Prints message with debug info about failed test
//!
//! @param [in] quads          Array of structures of type SquareEquation
//! @param [in] i              Number of test
//! @param [in] tests_filename Name of file that used to read tests
//!
//! @see SquareEquation
//--------------------------------------------------------------

void PrintTestError(SquareEquation *const quads, const int i, const char *const tests_filename);

//--------------------------------------------------------------
//! Prints success message when all tests passed
//--------------------------------------------------------------

void PrintTestSuccess();

#endif // QUADRATIC_PRINT_HPP
