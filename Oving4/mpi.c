#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../common/common.h"


void vecSum(int N, int nproc, int myid) {
    double vectorSum = 0, pi = 4.0*atan(1.0), mySum = 0;
    int *ofs, *cols;
    //splitVector(N, nproc, &cols, &ofs);
    //Vector vector = createVector(cols[myid]);

    for (long int i=myid+1; i<=N; i+=nproc) {
        double temp=1.0/(i*i);
        //vector->data[i] = temp;
        mySum += temp;
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
