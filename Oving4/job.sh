#!/bin/bash

#PBS -N test
#PBS -lnodes=1:ppn=12:default
#PBS -lwalltime=00:01:00
#PBS -lpmem=100MB
#PBS -A freecycle
#PBS -q optimist
#PBS -j oe

cd ${PBS_O_WORKDIR}

module load intelcomp
module load openmpi/1.4.3-intel
KMP_AFFINITY="granularity=fine,compact"

echo "===== Serial results ====="
./serial

echo "===== OpenMP results ====="
OMP_NUM_THREADS=4 ./openmp

echo "===== MPI results ====="
OMP_NUM_THREADS=4 mpirun -np 2 mpi

OMP_NUM_THREADS=4 mpirun -np 8 mpi
