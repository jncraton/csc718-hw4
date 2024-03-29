#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

int is_valid(int num) {
  int sum = 0;
  char buf[11];
  sprintf(buf, "%u", num);

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

  // Buffer overflow test
  assert(is_valid(-1111111111));
  assert(is_valid(1212121212));
}

int main() {
  int i, sum=0, count;

  test();

  /*
  1. The identifier is a six-digit combination of the numerals 0-9
  2. The first digit may not be a 0.
  3. Two consecutive digits may not be the same.
  4. The sum of the digits may not be 7, 11, or 13.
  */

  omp_set_num_threads(4);

  for (int runs=0; runs < 100; runs++) {
    sum=0;
    // Loop conditions enforce the first two requirements
    #pragma omp parallel for private(i) reduction(+: sum)
    for (i = 100000; i <= 999999; i++) {
      if (is_valid(i)) {
        sum++;
      }
    }
  }

  printf("Sum: %d\n", sum);
}
