all: seq mpi

seq: seq.c
	gcc seq.c -o seq
	./seq

mpi: mpi.c
	mpicc mpi.c -o mpi
	mpirun -n 4 ./mpi

clean:
	rm -f seq mpi