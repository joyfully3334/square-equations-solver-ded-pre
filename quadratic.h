enum INPUT_ERRORS {
  no_input_errors = 0,
  not_a_number    = 1,
  not_finite      = 2
};
enum PRINT_RESULTS_ERRORS {
  no_print_results_errors       = 0,
  undefined_amount_of_solutions = 1,
};
enum AMOUNT_OF_SOLUTIONS {
  undefined_solutions = -1,
  zero_solutions      =  0,
  one_solution        =  1,
  two_solutions       =  2,
  inf_solutions       =  3,
};
const double EPS = 1e-5;

struct SquareEquation {
  double a, b, c, x1, x2;
  AMOUNT_OF_SOLUTIONS number_of_solutions;
};

INPUT_ERRORS ReadCoef(double *coef, const char name);

INPUT_ERRORS ReadInput(SquareEquation *quad);

int InputErrorHandler(const INPUT_ERRORS read_result);

int ZeroComp(const double num);

void RemoveNegativeZero(double *num);

void SolveEquation(SquareEquation *quad);

void GetQuadraticSolution(const double a, const double b, const double c,
                          double *x1, double *x2,
                          AMOUNT_OF_SOLUTIONS *number_of_solutions);

void GetLinearSolution(const double b, const double c, double *x1,
                  AMOUNT_OF_SOLUTIONS *number_of_solutions);

PRINT_RESULTS_ERRORS PrintResult(const SquareEquation quad);

