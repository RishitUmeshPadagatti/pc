#include <stdio.h>
#include <omp.h>

int main(){
    omp_set_num_threads(4);

    #pragma omp parallel for 
    for (int i = 0; i < 8; i++){
        printf("Number %d from thread %d\n", i, omp_get_thread_num());
    }

    return 0;
}

// gcc-16 -fopenmp program.c -o program
// ./program 

// #pragma omp parallel
// #pragma omp parallel for 
// omp_set_num_threads(4);
// int id = omp_get_thread_num();