#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <mpi.h>


using namespace std;

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int rank, world;

    MPI_Comm_size(MPI_COMM_WORLD, &world);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    printf("Hello: rank %d, world: %d\n",rank, world);
    
    MPI_Finalize();
    return 0;
}