#include <math.h>
#include <stdio.h>

#include "quadratic_equation.hpp"
#include "quadratic_input.hpp"
#include "quadratic_print.hpp"
#include "quadratic_solve.hpp"
#include "quadratic_utils.hpp"
#include "quadratic_tests.hpp"

static int ExecuteProgramm();

int main(int argc, char **argv) {
  if (CheckFlag(argc, argv, "--slient")) {
    printf("%s\n", "--Square equation solver--");
  }
  if (!CheckFlag(argc, argv, "--help")) {
    printf("%s\n%s\n%s\n%s\n%s\n",
           "Usage: quadratic [options]",
           "Options:",
           "  --help       Display this information.",
           "  --self-check Check tests from test.txt",
           "  --silent     Dont print welocme message");
  } else if (!CheckFlag(argc, argv, "--self-check")) {
    FILE *tests_fp = fopen("tests.txt", "r");
    if (!tests_fp) {
      fprintf(stderr, "Unable to open test.txt file");
      return 1;
    }
    return ExecuteProgrammWithTesting("tests.txt");
  } else {
    return ExecuteProgramm();
  }

  return 0;
}

static int ExecuteProgramm() {
  SquareEquation quad1;
  if (InputErrorHandler(ReadInput(&quad1)))
    return 1;

  printf("Solving equation: %lfx^2 %c %lfx %c %lf = 0\n", quad1.a,
         (quad1.b >= 0 ? '+' : '-'), fabs(quad1.b),
         (quad1.c >= 0 ? '+' : '-'), fabs(quad1.c));

  SolveEquation(&quad1);
  if (PrintResult(quad1))
    return 1;

  return 0;
}

