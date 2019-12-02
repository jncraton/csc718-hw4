all: seq mpi

seq: seq.c
	gcc seq.c -o seq
	./seq

mpi: mpi.c
	mpicc seq.c -o mpi
	mpirun -n 4 ./mpi