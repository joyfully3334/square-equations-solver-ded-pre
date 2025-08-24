#include <math.h>
#include <stdio.h>

#include "quadratic_equation.hpp"
#include "quadratic_input.hpp"
#include "quadratic_print.hpp"
#include "quadratic_solve.hpp"
#include "quadratic_utils.hpp"
#include "quadratic_tests.hpp"

int main(int argc, char **argv) {
  if (!CheckFlag(argc, argv, "--silent"))
    PrintWelcome();

  if (CheckFlag(argc, argv, "--help")) {
    PrintHelp();
    return 1;
  }

  if (CheckFlag(argc, argv, "--self-check")) {
    FILE *tests_fp = fopen("tests.txt", "r");
    if (!tests_fp) {
      fprintf(stderr, "Unable to open test.txt file");
      return 1;
    }
    return ExecuteProgrammWithTesting();
  } else {
    SquareEquation quad1;
    if (CheckFlag(argc, argv, "--parse")) {
      if (InputErrorHandler(ParseInput(&quad1)))
        return 1;
    } else {
      if (InputErrorHandler(ReadInput(&quad1)))
        return 1;
    }


    printf("Solving equation: %lgx^2 %c %lgx %c %lg = 0\n", quad1.a,
          (quad1.b >= 0 ? '+' : '-'), fabs(quad1.b),
          (quad1.c >= 0 ? '+' : '-'), fabs(quad1.c));

    SolveEquation(&quad1);
    if (PrintResult(quad1))
      return 1;

    return 0;
}

return 0;
}
