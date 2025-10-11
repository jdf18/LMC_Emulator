#include "collatz.h"

int collatz(int n) {
  if (n == 1) return 1;
  if (n % 2 == 0) return n / 2;
  return (3 * n + 1) / 2;
}
