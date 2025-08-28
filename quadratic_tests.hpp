#ifndef QUADRATIC_TESTS_HPP
#define QUADRATIC_TESTS_HPP

#include "quadratic_equation.hpp"

//--------------------------------------------------------------
//! Executes tests
//!
//! Reads tests, then runs tests and compairing it
//!
//! @param [in] tests_filename Name of file to read from
//! @param [in] is_parsing     If non-zero, use parsing version for this file
//!
//! @return Non-zero value on error, else 0
//--------------------------------------------------------------

int ExecuteTests(const char *const tests_filename, const int is_parsing);

//--------------------------------------------------------------
//! Reads tests from file
//!
//! @param [in] filename    Name of file to read from
//! @param [in] tests_count Amount of tests if file
//! @param [in] quads       Array of structs of type SquareEquation
//!
//! @return Non-zero value on error, else 0
//--------------------------------------------------------------

int ReadTests(const char *const filename, const int tests_count, SquareEquation quads[]);

//--------------------------------------------------------------
//! Parses tests from file
//!
//! @param [in] filename    Name of file to read from
//! @param [in] tests_count Amount of tests if file
//! @param [in] quads       Array of structs of type SquareEquation
//!
//! @return Non-zero value on error, else 0
//--------------------------------------------------------------

int ParseTests(const char *const filename, const int tests_count, SquareEquation quads[]);

//--------------------------------------------------------------
//! Runs one test
//!
//! Compairing readed answer with calculated
//!
//! @param [in] quad Structure of type SquareEquation with readed answer
//!
//! @return Non-zero value on error, else 0
//--------------------------------------------------------------

int RunTest(SquareEquation *const quad);

#endif // QUADRATIC_TESTS_HPP
