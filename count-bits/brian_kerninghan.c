#include <limits.h>

unsigned int nondet_uint();

unsigned int count_bits_ref(unsigned int x) {
  unsigned int c;
  for (int i = 0; i < sizeof(unsigned int) * 8; i++) {
    c += x & 1;
    x >>= 1;
  }
  return c;
}

// unsigned int x; // count the number of bits set in x
// unsigned int c; // c accumulates the total bits set in x
unsigned int brain_kerninghan(unsigned int x) {
  unsigned int c;
  for (c = 0; x; c++) {
    x &= x - 1; // clear the least significant bit set
  }
  return c;
}

int main() {
  unsigned int x = nondet_uint();
  __CPROVER_assume(x >= 0 && x <= UINT_MAX);
  unsigned int res_ref = count_bits_ref(x);
  unsigned int res_bit = brain_kerninghan(x);
  __CPROVER_assert(res_ref == res_bit,
                   "Err: brain_kerninghan did not return the same value as "
                   "count_bits_ref");
}
