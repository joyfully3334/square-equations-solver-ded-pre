#ifndef QUADRATIC_INPUT_HPP
#define QUADRATIC_INPUT_HPP

#include <stdio.h>

#include "quadratic_equation.hpp"

//--------------------------------------------------------------
//! Reads three numbers in `double` type
//!
//! Reads coefficients from input_fp to quad
//!
//! @param [in] quad     Square equation where function puts coefficients
//! @param [in] input_fp Pointer to a stream where function reads coefficients
//---------------------------------------------------------------

int ReadInput(SquareEquation *const quad, FILE *const input_fp);

//--------------------------------------------------------------
//! Parses coefficients from strings like ax^2 + bx + c
//!
//! Reads coefficients from input_fp to quad
//!
//! @param [in] quad     Square equation where function puts coefficients
//! @param [in] input_fp Pointer to a stream where function reads coefficients
//---------------------------------------------------------------

int ParseInput(SquareEquation *const quad, FILE *const input_fp);

#endif // QUADRATIC_INPUT_HPP
