#include <stdio.h>
#include <math.h>
#include <time.h>

double current_value(int value)
{
  double signal;
  int denominator;

  signal = pow(-1, value - 1);
  denominator = 2 * value - 1;

  return signal * (1.0 / denominator);
}

double get_pi(int num)
{
  double response;
  int iteration;

  response = 1;
  iteration = num;

  while (iteration > 1)
  {
    response = response + current_value(iteration);
    iteration--;
  }

  return 4 * response;
}

int test_value(double value)
{
  clock_t start, end;
  double execution_time;
  start = clock();

  printf(" >> PI: %.8lf\n", get_pi(value));

  end = clock();
  execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
  printf("This script run in %.8lf seconds", execution_time);

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
