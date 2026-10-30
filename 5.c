#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]){
    int rank, size;
    int number;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2){
        if (rank == 0){
            printf("Error: This program required at least 2 MPI process \n");
        }
        MPI_Finalize();
        return 0;
    }

    // process 0 sends the data
    if (rank == 0){
        number = 42;
        printf("Sending number %d to Process 0\n", number);
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }

    // process 1 receives the data
    if (rank == 1){
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received number %d in Process 1\n", number);
    }

    MPI_Finalize();

    return 0;
}

// mpicc 5.c -o 5 
// mpirun -np 2 ./5 