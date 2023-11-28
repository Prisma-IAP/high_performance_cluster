#include <stdio.h>
#include <math.h>
#include <time.h>

/*
 * Function:   factorial
 * ---------------------
 * calculate a natural factorial using the recursion:
 *     value! = value * (value - 1)!
 *
 *  value: integer number
 *
 *  returns: an integer major than 0
 *
 */
int factorial(int value)
{
  if (value < 2)
  {
    return 1;
  }

  return value * factorial(value - 1);
}

/*
 * Function:  maclaurin
 * --------------------
 * computes an approximation of e^x using:
 *    e^exponent = sum[n=0 to limit] (exponent^n / n!)
 *
 *  exponent: double exponent of euler number
 *  limit: integer maximum number of iterations
 *
 *  returns: the approximate value of e^x by summing the first limit terms
 *           in the above series
 */
double maclaurin(double exponent, int limit)
{
  double response;
  int iteration;

  response = 0.0;
  iteration = 0;

  while (iteration < limit)
  {
    int denominator;
    double item;

    denominator = factorial(iteration);
    item = (double)(pow(exponent, iteration)) / (double)(denominator);
    response = response + item;
    iteration = iteration + 1;
  }

  return response;
}

/*
 * Function:  test_value
 * --------------------
 * test a single value of the maclaurin series
 *
 *  value: double exponent of euler number
 *
 *  uses the tested limit of iterations 900
 *
 *  print the result and the time the program take on the execution
 *
 *  returns: integer
 */
int test_value(double value)
{
  clock_t start, end;
  double execution_time;
  start = clock();

  printf(" >> e^%.4lf = %.8lf\n", value, maclaurin(value, 900));

  end = clock();
  execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("    This script run in %.8lf seconds", execution_time);

  return 0;
}

int main()
{
  double test_values[10] = {1.0e0, 1.0e1, 1.0e2, 1.0e3, 1.0e4,
                            1.0e5, 1.0e6, 1.0e7, 1.0e8, 1.0e9};
  int iteration;

  for (iteration = 0; iteration < 10; iteration++)
  {
    printf("%.1lf iterations:\n", test_values[iteration]);
    test_value(test_values[iteration]);
    printf("\n\n");
  }

  return 0;
}
