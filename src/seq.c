#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int has_repetition(int num) {
  char buf[10];
  sprintf(buf, "%d", num);

  for (int i = 1; i < 6; i++) {
    if (buf[i-1] == buf[i]) { return 1; }
  }

  return 0;
}

int has_valid_sum(int num) {
  int sum = 0;
  char buf[10];
  sprintf(buf, "%d", num);

  for (int i = 0; i < 6; i++) {
    sum += buf[i] - 48;
  }

  return (sum != 7 && sum != 11 && sum != 13);  
}

void test() {
  assert(has_repetition(999999));
  assert(has_repetition(123455));
  assert(has_repetition(112345));
  assert(has_repetition(123345));
  assert(!has_repetition(123456));
  assert(!has_repetition(987565));

  assert(has_valid_sum(111111));
  assert(has_valid_sum(123456));
  assert(has_valid_sum(869205));
  assert(!has_valid_sum(111112));
  assert(!has_valid_sum(115112));
  assert(!has_valid_sum(111116));
  assert(!has_valid_sum(111118));
  assert(!has_valid_sum(611311));
}

int main() {
  int i, sum, count;

  test();

  /*
  1. The identifier is a six-digit combination of the numerals 0-9
  2. The first digit may not be a 0.
  3. Two consecutive digits may not be the same.
  4. The sum of the digits may not be 7, 11, or 13.
  */

  // Loop conditions enforce the first two requirements
  for (i = 100000; i <= 999999; i++) {
    if (!has_repetition(i) && has_valid_sum(i)) {
      sum++;
    }
  }

  printf("Sum: %d\n", sum);
}