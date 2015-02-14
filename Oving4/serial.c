#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../common/common.h"


void vecSum(int N) {
    double vectorSum = 0, pi = 4.0*atan(1.0);
    Vector vector = createVector(N);

    for (long int i=1; i<=N; i++) {
        double temp=1.0/(i*i);
        vector->data[i] = temp;
        vectorSum += temp;
    }


    printf("N = %d | Vector sum: %f\n", N, vectorSum);
    printf("Difference: %1.16f\n\n", pi*pi/6.0 - vectorSum);
}


int main(int argc, char** argv) {
    for(int i=8; i<=16384; i*=2) {
        vecSum(i);
    }
}
