all: omp seq mpi

seq: seq.c
	gcc $< -o $@
	time ./$@

omp: omp.c
	gcc $< -fopenmp -o $@
	time ./$@

mpi: mpi.c
	mpicc mpi.c -o mpi
	time mpirun -np 4 ./mpi

clean:
	rm -f seq mpi omp