module load intel/compilers/11.1.059
module load cmake
CC=icc FC=ifort cmake . -DCMAKE_BUILD_TYPE=Release

make

qsub job.sh
showq | grep valerijf
