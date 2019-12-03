all: omp seq mpi

seq: seq.c
	gcc $< -o $@
	./$@

omp: omp.c
	gcc $< -fopenmp -o $@
	./$@

mpi: mpi.c
	mpicc mpi.c -o mpi
	mpirun -np 4 ./mpi

clean:
	rm -f seq mpi omp