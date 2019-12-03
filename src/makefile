all: omp seq mpi

seq: seq.c
	gcc $< -o $@
	time -p ./$@

omp: omp.c
	gcc $< -fopenmp -o $@
	time -p ./$@

mpi: mpi.c
	mpicc mpi.c -o mpi
	time -p mpirun -np 4 ./mpi

clean:
	rm -f seq mpi omp