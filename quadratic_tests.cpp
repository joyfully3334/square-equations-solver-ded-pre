#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_input.hpp"
#include "quadratic_print.hpp"
#include "quadratic_solve.hpp"
#include "quadratic_tests.hpp"
#include "quadratic_utils.hpp"

static int ReadOneTest(FILE *fp, SquareEquation *const quad);

static int ParseOneTest(FILE *fp, SquareEquation *const quad);

int ExecuteTests(const char *tests_filename, const int is_parsing) {
  int amount_of_lines = GetAmountOfLines(tests_filename);
  SquareEquation *quads = (SquareEquation *)calloc((size_t)amount_of_lines, sizeof(SquareEquation));

  if (is_parsing)
    ParseTests(tests_filename, amount_of_lines, quads);
  else
    ReadTests(tests_filename, amount_of_lines, quads);

  for (int i = 0; i < (int)amount_of_lines; ++i) {
    if (RunTest(&quads[i])) {
      PrintTestError(quads, i, tests_filename);
      free(quads);
      quads = 0;
      return 1;
    }
  }
  free(quads);
  quads = 0;
  PrintTestSuccess();
  return 0;
}

int RunTest(SquareEquation *const quad) {
  assert(quad);

  SquareEquation new_quad = *quad;
  SolveEquation(&new_quad);
  if (QuadraticComp(*quad, new_quad))
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

  int amount_of_solutions = 0.;
  ReadInput(quad, fp);
  while (fgetc(fp) != '@')
    ;
  fscanf(fp, "%d", &amount_of_solutions);
  switch (amount_of_solutions) {
    case 0:
      quad->number_of_solutions = zero_solutions;
      break;
    case 1:
      fscanf(fp, "%lg", &quad->x1);
      quad->number_of_solutions = one_solution;
      break;
    case 2:
      fscanf(fp, "%lg%lg", &quad->x1, &quad->x2);
      if (quad->x1 > quad->x2) {
        double tmp = quad->x2;
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

int ParseTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]) {
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
    } else if ((tmp = ParseOneTest(fp, &quads[i]))) {
      fclose(fp);
      return tmp;
    }
  }
  fclose(fp);
  return 0;
}

static int ParseOneTest(FILE *fp, SquareEquation *const quad) {
  assert(fp);
  assert(quad);

  ParseInput(quad, fp);
  double tmp = 0.;
  double amount_of_solutions = 0.;
  fscanf(fp, "%lg", &amount_of_solutions);
  switch ((int)amount_of_solutions) {
    case 0:
      quad->number_of_solutions = zero_solutions;
      break;
    case 1:
      fscanf(fp, "%lg", &quad->x1);
      quad->number_of_solutions = one_solution;
      break;
    case 2:
      fscanf(fp, "%lg%lg", &quad->x1, &quad->x2);
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
  char ch_tmp = ' ';
  fscanf(fp, "%c", &ch_tmp);
  return 0;
}
