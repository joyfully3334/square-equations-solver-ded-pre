#include <stdio.h>

#include "quadratic_print.hpp"

PRINT_RESULTS_ERRORS PrintResult(const SquareEquation quad) {
  switch (quad.number_of_solutions) {
    case zero_solutions: 
      printf("There is no solution for this square equation\n");
      break;
    case one_solution:
      printf("Solution has found: x = %lg\n", quad.x1);
      break;
    case two_solutions:
      printf("Solution has found: x1 = %lg, x2 = %lg\n", quad.x1, quad.x2);
      break;
    case inf_solutions:
      printf("Every possible x is allowed for this equation\n");
      break;
    case undefined_solutions:
      fprintf(stderr, "Invalid arguments in PrintResult function: Undefined amount of solutions\n");
      return undefined_amount_of_solutions;
    default:
      fprintf(stderr, "Invalid arguments in PrintResult function: Unknown amount of solutions\n");
      return undefined_amount_of_solutions;
  }

  return no_print_results_errors;
}

void PrintWelcome() {
  printf("%s\n", "--Square equation solver--");
}
void PrintHelp() {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n",
           "Usage: quadratic [options]",
           "Options:",
           "  --help       Display this information.",
           "  --self-check Check tests from test.txt.",
           "  --silent     Dont print welocme message.",
           "  --parse      Use parsing version of programm.");
}
