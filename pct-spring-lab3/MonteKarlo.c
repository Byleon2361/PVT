#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <stdio.h>
const double PI = 3.14159265358979323846;
double func(double x, double y)
{
    return exp(x - y);
}

double getrand(unsigned int *seed)
{
    return (double)rand_r(seed) / RAND_MAX;
}
int main(int argc, char **argv)
{
    for (int p = 0; p <= 8; p += 2)
    {
        const int n = 100000000;
        printf("Numerical integration by Monte Carlo method: n = %d\n", n);
        int in = 0;
        double s = 0;
        omp_set_num_threads(p);
#pragma omp parallel
        {
            double s_loc = 0;
            int in_loc = 0;
            unsigned int seed = omp_get_thread_num();
#pragma omp for nowait
            for (int i = 0; i < n; i++)
            {
                double x = getrand(&seed) * -1; /* x in [-1, 0] */
                double y = getrand(&seed);      /* y in [0, 1] */
                if (y <= 1)
                {
                    in_loc++;
                    s_loc += func(x, y);
                }
            }
#pragma omp atomic
            s += s_loc;
#pragma omp atomic
            in += in_loc;
        }
        double v = PI * in / n;
        double res = v * s / in;
        printf("Result: %.12f, n %d\n", res, n);
    }
    return 0;
}