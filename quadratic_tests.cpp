#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_print.hpp"
#include "quadratic_solve.hpp"
#include "quadratic_tests.hpp"
#include "quadratic_utils.hpp"

static int ReadOneTest(FILE *fp, SquareEquation *const quad);

static int ParseOneTest(FILE *fp, SquareEquation *const quad);

int ExecuteTests() {
  unsigned long int amount_of_lines = 0;
  int ch = ' ';
  const char *tests_filename = "tests.txt";
  FILE *tests_fp = fopen(tests_filename, "r");
  if (!tests_fp) {
    fprintf(stderr, "Unable to open file %s\n", tests_filename);
    return 1;
}
  while ((ch = fgetc(tests_fp)) != EOF) {
    if (ch == '\n')
      ++amount_of_lines;
  }
  fclose(tests_fp);
  SquareEquation *quads = (SquareEquation *)calloc(amount_of_lines, sizeof(SquareEquation));
  ReadTests(tests_filename, (int)amount_of_lines, quads);
  for (int i = 0; i < (int)amount_of_lines; ++i) {
    if (RunTest(&quads[i])) {
      PrintTestError(quads, i, tests_filename);
      free(quads);
      quads = 0;
      return 1;
    }
  }
  amount_of_lines = 0;
  tests_filename = "tests_parse.txt";
  tests_fp = fopen(tests_filename, "r");
  if (!tests_fp) {
    fprintf(stderr, "Unable to open file %s\n", tests_filename);
    free(quads);
    quads = 0;
    return 1;
  }
  while ((ch = fgetc(tests_fp)) != EOF) {
    if (ch == '\n')
      ++amount_of_lines;
  }
  fclose(tests_fp);
  quads = (SquareEquation *)realloc(quads, amount_of_lines * sizeof(SquareEquation));
  ParseTests(tests_filename, (int)amount_of_lines, quads);
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

  char ch = ' ';
  fscanf(fp, "%lg%lg%lg", &quad->a, &quad->b, &quad->c);
  while ((ch = (char)fgetc(fp)) != '@')
    ;
  double tmp = 0;
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

  double tmp = 0;
  int ch = 0;
  int deg = 0, changed = 0, after_dot = 0, prev_mark = 1;
  double nums[3] = {0., 0., 0.};
  for (int i = 0; (ch = fgetc(fp)) != EOF; ++i) {
    if (isdigit(ch) && deg != 2 && !after_dot) {
      changed = 1;
      tmp = tmp * 10 + (ch - '0');
    } else if (isdigit(ch) && deg != 2 && after_dot) {
      changed = 1;
      tmp += (ch - '0') * pow(10, -after_dot);
      ++after_dot;
    } else if (ch == '.') {
      after_dot = 1;
    } else if (ch == 'x') {
      deg = 1;
    } else if (ch == '^') {
      deg = 2;
    } else if (ch == '+' || ch == '-' || ch == '\0' || ch == '\n' || ch == '@') {
      nums[deg] += (!changed && deg ? prev_mark : tmp * prev_mark);
      prev_mark = (ch == '+' ? 1 : -1);
      tmp = 0.;
      changed = deg = after_dot = 0;
      if (ch == '\0' || ch == '\n' || ch == '@')
        break;
    }
  }
  quad->c = nums[0];
  quad->b = nums[1];
  quad->a = nums[2];
  tmp = 0.;
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
