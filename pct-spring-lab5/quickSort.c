#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int threadshold = 100000;
int getRand()
{
    return rand();
}
double
omp_get_wtime()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec + ts.tv_nsec * 1E-9;
}
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void partition(int *v, int *i, int *j, int low, int high)
{
    *i = low;
    *j = high;
    int pivot = v[(low + high) / 2];
    do
    {
        while (v[*i] < pivot)
            (*i)++;
        while (v[*j] > pivot)
            (*j)--;
        if (*i <= *j)
        {
            swap(&v[*i], &v[*j]);
            (*i)++;
            (*j)--;
        }
    } while (*i <= *j);
}
void quicksort(int *v, int low, int high)
{
    int i = 0;
    int j = 0;
    partition(v, &i, &j, low, high);
    if (low < j)
        quicksort(v, low, j);
    if (i < high)
        quicksort(v, i, high);
}
void quicksort_tasks(int *v, int low, int high)
{
    int i, j;
    partition(v, &i, &j, low, high);
    if (high - low < threadshold || (j - low < threadshold || high - i < threadshold))
    {
        if (low < j)
            quicksort_tasks(v, low, j);
        if (i < high)
            quicksort_tasks(v, i, high);
    }
    else
    {
#pragma omp task
        {
            quicksort_tasks(v, low, j);
        }
        quicksort_tasks(v, i, high);
    }
}
int main()
{
    srand(time(NULL));
    FILE *file;
    file = fopen("quickSort.dat", "w");

    double serialTime = 0;
    double parallelTime = 0;
    int n = 1000000;
    int *array = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        array[i] = getRand();
    }
    serialTime = omp_get_wtime();
    quicksort(array, 0, n - 1);
    serialTime = omp_get_wtime() - serialTime;
    printf("Non parallel time: %.6f\n", serialTime);

    for (int i = 2; i <= 8; i += 2)
    {
        for (int i = 0; i < n; i++)
        {
            array[i] = getRand();
        }
        parallelTime = omp_get_wtime();
#pragma omp parallel num_threads(i)
        {
#pragma omp single
            quicksort_tasks(array, 0, n - 1);
        }
        parallelTime = omp_get_wtime() - parallelTime;
        printf("Tasks time: %.6f\n", parallelTime);
        fprintf(file, "%d   %f\n", i, serialTime / parallelTime);
    }

    fclose(file);
    free(array);
    return 0;
}