#include <stdio.h>
#include "quadratic.hpp"

PRINT_RESULTS_ERRORS PrintResult(const SquareEquation quad) {
  switch (quad.number_of_solutions) {
    case zero_solutions: 
      printf("There is no solution for this square equation\n");
      break;
    case one_solution:
      printf("Solution has found: x = %lf\n", quad.x1);
      break;
    case two_solutions:
      printf("Solution has found: x1 = %lf, x2 = %lf\n", quad.x1, quad.x2);
      break;
    case inf_solutions:
      printf("Every possible x is allowed for this equation\n");
      break;
    case undefined_solutions:
      printf("Invalid arguments in PrintResult function: Undefined amount of solutions\n");
      return undefined_amount_of_solutions;
    default:
      printf("Invalid arguments in PrintResult function: Unknown amount of solutions\n");
      return undefined_amount_of_solutions;
  }
  return no_print_results_errors;
}
