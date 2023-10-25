#include <limits.h>

int nondet_int();

int abs_ref(int x) { return x < 0 ? -x : x; }

int abs_bit(int x) {
  int m = x >> 31;
  return (x ^ m) + ~m + 1;
}

int main() {
  int x = nondet_int();
  int res_ref = abs_ref(x);
  int res_bit = abs_bit(x);
  __CPROVER_assert(res_ref == res_bit,
                   "reference implementation abs_ref returned the same value "
                   "as the bit-twiddling version abs_bit");
}
