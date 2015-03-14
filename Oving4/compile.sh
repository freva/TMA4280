CXX=icpc CC=icc FC=ifort cmake CMakeLists.txt
make

qsub job.sh
showq | grep valerijf
