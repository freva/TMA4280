#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "../common/common.h"


void vecSum(int N, int nproc, int myid) {
    double vectorSum = 0, pi = 4.0*atan(1.0), mySum = 0;
    int n = N/nproc;
    
    MPI_Status status;
    if(myid == 0) {
        Vector allElements = createVector(N);

		#pragma omp parallel for schedule(static)
        for(int i=1; i<=N; i++) {
            allElements->data[i] = 1.0/(i*i);
        }

        for(int proc=0; proc < nproc; proc++) {
            MPI_Send(&(allElements->data[proc*n]), n, MPI_DOUBLE, proc, 1, MPI_COMM_WORLD);
        }
    }

    Vector myVector = createVector(n);
    MPI_Recv(myVector->data, n, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);


    #pragma omp parallel for schedule(static) reduction(+:mySum)
    for (int i=0; i<n; i++) {
        mySum += myVector->data[i];
    }

    MPI_Reduce(&mySum, &vectorSum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    if(myid == 0) {
        printf("N = %d | Vector sum: %f\n", N, vectorSum);
        printf("Difference: %1.16f\n\n", pi*pi/6.0 - vectorSum);
    }
}


int main(int argc, char **argv) {
    int myid, nproc;
    double startTime;

    init_app(argc, argv, &myid, &nproc);

    if((nproc & (nproc - 1)) != 0) { //Checks if size is power of 2. Assumes non-zero
        close_app();
        return 0;
    }

    for(int i=8; i<=16384; i*=2) {
        vecSum(i, nproc, myid);
    }

    close_app();
}
