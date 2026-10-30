
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Recursive Fibonacci using OpenMP tasks
long long fib_task(int n)
{
    if (n < 2)
        return n;

    long long x, y;

    #pragma omp task shared(x)
    x = fib_task(n - 1);

    #pragma omp task shared(y)
    y = fib_task(n - 2);

    #pragma omp taskwait

    return x + y;
}

int main()
{
    int m;

    printf("Enter number of Fibonacci numbers to compute: ");
    scanf("%d", &m);

    if (m <= 0) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    long long *fib_array =
        (long long *)malloc(m * sizeof(long long));

    if (fib_array == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    #pragma omp parallel
    {
        #pragma omp single
        {
            for (int i = 0; i < m; i++) {

                #pragma omp task shared(fib_array) firstprivate(i)
                fib_array[i] = fib_task(i);
            }

            // Wait for all Fibonacci tasks to finish
            #pragma omp taskwait
        }
    }

    printf("Fibonacci numbers:\n");

    for (int i = 0; i < m; i++) {
        printf("Fib(%d) = %lld\n", i, fib_array[i]);
    }

    free(fib_array);

    return 0;
}
