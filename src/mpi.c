#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <mpi.h>

int is_valid(int num) {
  int sum = 0;
  char buf[10];
  sprintf(buf, "%d", num);

  for (int i = 0; i < 6; i++) {
    if (i > 0 && buf[i-1] == buf[i]) { return 0; }
    sum += buf[i] - 48;
  }

  return (sum != 7 && sum != 11 && sum != 13);  
}

void test() {
  // Repetition tests
  assert(!is_valid(999999));
  assert(!is_valid(123455));
  assert(!is_valid(112345));
  assert(!is_valid(123345));
  assert(is_valid(123456));
  assert(is_valid(987565));

  // Sum tests
  assert(is_valid(101010));
  assert(is_valid(123456));
  assert(is_valid(869205));
  assert(!is_valid(101032));
  assert(!is_valid(205202));
  assert(!is_valid(202016));
  assert(!is_valid(202018));
  assert(!is_valid(620320));
}

int main(int argc, char **argv) {
  int id, i, count=0, global_count, num_procs;

  test();

  MPI_Init (&argc, &argv);
  MPI_Barrier(MPI_COMM_WORLD);

  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
  MPI_Comm_rank (MPI_COMM_WORLD, &id);

  /*
  1. The identifier is a six-digit combination of the numerals 0-9
  2. The first digit may not be a 0.
  3. Two consecutive digits may not be the same.
  4. The sum of the digits may not be 7, 11, or 13.
  */

  for (int runs=0; runs < 100; runs++) {
    count=0;
    // Loop conditions enforce the first two requirements
    for (i = 100000+id; i <= 999999; i+=num_procs) {
      if (is_valid(i)) {
        count++;
      }
    }
  }

  MPI_Reduce (&count, &global_count, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Finalize();

  if (!id) printf("Count: %d\n", global_count);
}
