
#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

// Function to check whether a number is prime
int is_prime(int num) {
    if (num <= 1)
        return 0;

    if (num == 2)
        return 1;

    if (num % 2 == 0)
        return 0;

    int limit = (int)sqrt(num);

    for (int i = 3; i <= limit; i += 2) {
        if (num % i == 0)
            return 0;
    }

    return 1;
}

int main() {
    int n;

    printf("Enter the value of n: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Please enter a positive number.\n");
        return 1;
    }

    int *prime_serial = malloc((n + 1) * sizeof(int));
    int *prime_parallel = malloc((n + 1) * sizeof(int));

    if (prime_serial == NULL || prime_parallel == NULL) {
        printf("Memory allocation failed.\n");
        free(prime_serial);
        free(prime_parallel);
        return 1;
    }

    for (int i = 0; i <= n; i++) {
        prime_serial[i] = 0;
        prime_parallel[i] = 0;
    }

    // Serial Execution
    double start_serial = omp_get_wtime();

    for (int i = 1; i <= n; i++) {
        prime_serial[i] = is_prime(i);
    }

    double end_serial = omp_get_wtime();

    // Parallel Execution
    double start_parallel = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int i = 1; i <= n; i++) {
        prime_parallel[i] = is_prime(i);
    }

    double end_parallel = omp_get_wtime();

    // Verification
    int mismatch = 0;

    for (int i = 1; i <= n; i++) {
        if (prime_serial[i] != prime_parallel[i]) {
            mismatch = 1;
            printf("Mismatch found at %d\n", i);
            break;
        }
    }

    if (!mismatch) {
        printf("\nPrime numbers from 1 to %d are:\n", n);

        for (int i = 1; i <= n; i++) {
            if (prime_parallel[i]) {
                printf("%d ", i);
            }
        }

        printf("\n");
    } else {
        printf("Error: Serial and parallel results differ.\n");
    }

    // Execution Time
    printf("\nExecution Time:\n");

    printf("Serial: %.6f seconds\n",
           end_serial - start_serial);

    printf("Parallel: %.6f seconds\n",
           end_parallel - start_parallel);

    free(prime_serial);
    free(prime_parallel);

    return 0;
}

