#include <stdio.h>

#include "quadratic_print.hpp"
#include "quadratic_solve.hpp"

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

void PrintTestError(SquareEquation *const quads, const int i, const char *const tests_filename) {
  const char *RED = "\033[0;31m";
  const char *NO_COLOR = "\033[0m";

  SquareEquation quad_readed = quads[i];
  SquareEquation quad_expected = quads[i];

  fprintf(stderr, "%s", RED);
  fprintf(stderr, "Failed on test %d in %s\n", i + 1, tests_filename);
  SolveEquation(&quad_expected);
  printf("  Readed: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n",
          quad_readed.a, quad_readed.b, quad_readed.c,
          quad_readed.x1, quad_readed.x2, quad_readed.number_of_solutions);
  printf("Expected: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n",
          quad_expected.a, quad_expected.b, quad_expected.c,
          quad_expected.x1, quad_expected.x2, quad_expected.number_of_solutions);
  fprintf(stderr, "%s", NO_COLOR);
}

void PrintTestSuccess() {
  const char *GREEN = "\033[0;32m";
  const char *NO_COLOR = "\033[0m";

  printf("%s", GREEN);
  printf("All tests passed successfully\n");
  printf("%s", NO_COLOR);
}
