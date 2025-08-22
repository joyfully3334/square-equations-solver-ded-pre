#include <math.h>
#include <stdio.h>
#include <string.h>

#include "quadratic_equation.hpp"
#include "quadratic_input.hpp"
#include "quadratic_print.hpp"
#include "quadratic_solve.hpp"
#include "quadratic_utils.hpp"

static int ExecuteProgramm();

static int ExecuteProgrammTest(SquareEquation *const quad);

static int ExecuteProgrammWithTesting(const char *const filename);

static int CheckFlag(int argc, char **argv, const char *flag);

static int QuadraticComp(const SquareEquation quad1, const SquareEquation quad2);

int main(int argc, char **argv) {
  if (!CheckFlag(argc, argv, "--self-check")) {
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
  SquareEquation quad1 = {0., 0., 0., 0., 0., undefined_solutions};
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

static int ExecuteProgrammTest(SquareEquation *const quad) {
  SquareEquation old_quad = *quad;
  SolveEquation(quad);
  if (QuadraticComp(*quad, old_quad))
    return 1;

  return 0;
}

static int ExecuteProgrammWithTesting(const char *const filename) {
  const int MAX_SIZE = 81;
  SquareEquation quads[MAX_SIZE] = {};
  ReadTests(filename, MAX_SIZE, quads);
  for (int i = 0; i < MAX_SIZE; ++i) {
    if (ExecuteProgrammTest(&quads[i])) {
      fprintf(stderr, "Failed on test %d\n", i + 1);
      return 1;
    }
  }
  printf("All tests passed successfully\n");

  return 0;
}

static int CheckFlag(int argc, char **argv, const char *flag) {
  for (int i = 0; i < argc; ++i) {
    if (!strcmp(argv[i], flag))
      return 0;
  }

  return 1;
}

static int QuadraticComp(const SquareEquation quad1, const SquareEquation quad2) {
  if (quad2.changed == 0)
    return 0;
  if (DoubleComp(quad1.a, quad2.a) || DoubleComp(quad1.b, quad2.b) ||
      DoubleComp(quad1.c, quad2.c) || DoubleComp(quad1.number_of_solutions, quad2.number_of_solutions))
    return 1;
  switch (quad1.number_of_solutions) {
    case zero_solutions:
      return 0;
    case one_solution:
      return DoubleComp(quad1.x1, quad2.x1);
    case two_solutions:
      return DoubleComp(quad1.x1, quad2.x1) || DoubleComp(quad1.x2, quad2.x2);
    case inf_solutions:
      return 0;
    case undefined_solutions:
    default:
      return 1;
  }
}
