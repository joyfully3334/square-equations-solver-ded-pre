#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_equation.hpp"
#include "quadratic_solve.hpp"
#include "quadratic_tests.hpp"
#include "quadratic_utils.hpp"

static int ReadOneTest(FILE *fp, SquareEquation *const quad);

int ExecuteProgrammWithTesting(const char *const filename) {
  unsigned long int amount_of_lines = 0;
  char ch = ' ';
  FILE *fp = fopen(filename, "r");
  while ((ch = (char)fgetc(fp)) != EOF) {
    if (ch == '\n')
      ++amount_of_lines;
  }
  fclose(fp);
  SquareEquation *quads = (SquareEquation *)malloc(sizeof(SquareEquation) * amount_of_lines);
  ReadTests(filename, (int)amount_of_lines, quads);
  for (int i = 0; i < (int)amount_of_lines; ++i) {
    if (ExecuteProgrammTest(&quads[i])) {
      fprintf(stderr, "Failed on test %d\n", i + 1);
      return 1;
    }
  }
  free(quads);
  printf("All tests passed successfully\n");

  return 0;
}

int ExecuteProgrammTest(SquareEquation *const quad) {
  SquareEquation old_quad = *quad;
  printf("%lf %lf %d\n", quad->x1, quad->x2, quad->number_of_solutions);
  SolveEquation(quad);
  printf("T\n");
  printf("%lf %lf\n", quad->x1, old_quad.x1);
  printf("%lf %lf\n", quad->x2, old_quad.x2);
  printf("%d %d\n", quad->number_of_solutions, old_quad.number_of_solutions);
  if (QuadraticComp(*quad, old_quad))
    return 1;

  return 0;
}

int ReadTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]) {
  assert(filename);

  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stderr, "Programm failed to read file tests.txt");
    return 1;
  }
  int tmp = 0;
  for (int i = 0;; ++i) {
    if (i >= MAX_SIZE) {
      fclose(fp);
      return 1;
    } else if ((tmp = ReadOneTest(fp, &quads[i]))) {
      fclose(fp);
      return tmp;
    }
  }
  fclose(fp);
  return 0;
}

static int ReadOneTest(FILE *fp, SquareEquation *const quad) {
  assert(fp);
  assert(quad);

  char ch = ' ';
  fscanf(fp, "%lf%lf%lf", &quad->a, &quad->b, &quad->c);
  while ((ch = (char)fgetc(fp)) != '@')
    ;
  double tmp = 0;
  double amount_of_solutions = 0.;
  fscanf(fp, "%lf", &amount_of_solutions);
  switch ((int)amount_of_solutions) {
    case 0:
      quad->number_of_solutions = zero_solutions;
      break;
    case 1:
      fscanf(fp, "%lf", &quad->x1);
      quad->number_of_solutions = one_solution;
      break;
    case 2:
      fscanf(fp, "%lf%lf", &quad->x1, &quad->x2);
      if (quad->x1 > quad->x2) {
        tmp = quad->x2;
        quad->x2 = quad->x1;
        quad->x1 = tmp;
      }
      quad->number_of_solutions = two_solutions;
      break;
    case -1:
      quad->number_of_solutions = inf_solutions;
      break;
    default:
      quad->number_of_solutions = undefined_solutions;
      break;
  }
  return 0;
}
