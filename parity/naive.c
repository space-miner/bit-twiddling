#include <limits.h>
#include <stdbool.h>

unsigned int nondet_uint();

bool parity_ref(unsigned int x) {
  int count = 0;
  while (x != 0) {
    count += x & 1;
    x >>= 1;
  }
  return count % 2;
}

bool naive_parity(unsigned int x) {
  bool parity = false;
  while (x) {
    parity = !parity;
    x = x & (x - 1);
  }
  return parity;
}

int main() {
  unsigned int x = nondet_uint();
  __CPROVER_assume(x >= 0 && x <= UINT_MAX);
  unsigned int res_ref = parity_ref(x);
  unsigned int res_bit = naive_parity(x);
  __CPROVER_assert(res_ref == res_bit,
                   "reference implementation parity_ref produced the same "
                   "value as the bit-twiddling version naive_parity");
}
