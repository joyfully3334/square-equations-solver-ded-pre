#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>

#include "quadratic_equation.hpp"
#include "quadratic_utils.hpp"

static int ReadOneTest(FILE *fp, SquareEquation *const quad);

static int ReadOneAnswer(FILE *fp, SquareEquation *const quad);

const double EPS = 1e-5;

int DoubleComp(const double num1, const double num2) {
  if (num1 - num2 < -EPS)
    return -1;
  else if (fabs(num1 - num2) <= EPS)
    return 0;
  else
    return 1;
}

void RemoveNegativeZero(double *const num) {
  assert(num);

  *num = (DoubleComp(*num, 0.) ? *num : fabs(*num));
}

int ReadTests(const char *const filename, const int MAX_SIZE, SquareEquation quads[]) {
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return 1;
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
  double tmp = 0;
  int deg = 0, changed = 0, after_dot = 0, prev_mark = 1;
  double nums[3] = {0., 0., 0.};
  while ((ch = (char)fgetc(fp)) != EOF) {
    if (isdigit(ch) && deg != 2 && !after_dot) {
      quad->changed = 1;
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
    } else if (ch == '+' || ch == '-' || ch == '\0' || ch == '@' || ch == '\n') {
      nums[deg] += (!changed && deg ? prev_mark : tmp * prev_mark);
      prev_mark = (ch == '-' ? -1 : 1);
      tmp = 0.;
      deg = after_dot = 0;
      if (ch == '\0' || ch == '@' || ch == '\n')
        break;
    }
  }
  quad->c = nums[0];
  quad->b = nums[1];
  quad->a = nums[2];
  if (ch == '@')
    return ReadOneAnswer(fp, quad);
  return 0;
}

static int ReadOneAnswer(FILE *fp, SquareEquation *const quad) {
  assert(fp);
  assert(quad);

  char ch = (char)fgetc(fp);
  double tmp = 0;
  int changed = 0, num = 0, after_dot = 0, ignoring = 0, prev_mark = 1;
  double nums[2] = {0., 0.};
  switch (ch) {
    case '0':
      quad->number_of_solutions = zero_solutions;
      break;
    case '1':
      quad->number_of_solutions = one_solution;
      break;
    case '2':
      quad->number_of_solutions = two_solutions;
      break;
    case '!':
      quad->number_of_solutions = inf_solutions;
      break;
    default:
      quad->number_of_solutions = undefined_solutions;
      break;
  }
  while ((ch = (char)fgetc(fp)) != EOF) {
    if (ch == '#') {
      ignoring = 1;
    } else if (ignoring) {
      ;
    } else if (isdigit(ch) && !after_dot) {
      quad->changed = 1;
      changed = 1;
      tmp = tmp * 10 + (ch - '0');
    } else if (isdigit(ch) && after_dot) {
      tmp += (ch - '0') * pow(10, -after_dot);
      ++after_dot;
    } else if (ch == '.') {
      after_dot = 1;
    } else if (changed && (ch == ' ' || ch == '-' || ch == '\0' || ch == '#' || ch == '\n')) {
      nums[num] += tmp * prev_mark;
      num = 1 - num;
      prev_mark = (ch == '-' ? -1 : 1);
      tmp = 0.;
      changed = after_dot = 0;
      if (ch == '\0' || ch == '\n')
        break;
    } else if (ch == '-') {
      prev_mark = -1;
    } else if (ch == '\n') {
      break;
    }
  }
  quad->x1 = (nums[0] < nums[1] ? nums[0] : nums[1]);
  quad->x2 = (nums[0] < nums[1] ? nums[1] : nums[0]);
  return 0;
}
