#include <limits.h>

unsigned int nondet_uint();

// To initially generate the table algorithmically:
// BitsSetTable256[0] = 0;
// for (int i = 0; i < 256; i++)
// {
//   BitsSetTable256[i] = (i & 1) + BitsSetTable256[i / 2];
// }

static const unsigned char BitsSetTable256[256] = {
#define B2(n) n, n + 1, n + 1, n + 2
#define B4(n) B2(n), B2(n + 1), B2(n + 1), B2(n + 2)
#define B6(n) B4(n), B4(n + 1), B4(n + 1), B4(n + 2)
    B6(0), B6(1), B6(1), B6(2)};

unsigned int count_bits_ref(unsigned int x) {
  unsigned int c;
  for (int i = 0; i < sizeof(unsigned int) * 8; i++) {
    c += x & 1;
    x >>= 1;
  }
  return c;
}

// unsigned int x; // count the number of bits set in 32-bit value x
// unsigned int c; // c is the total bits set in x
unsigned int lookup_table_count_bits(unsigned int x) {
  return BitsSetTable256[x & 0xff] + BitsSetTable256[(x >> 8) & 0xff] +
         BitsSetTable256[(x >> 16) & 0xff] + BitsSetTable256[x >> 24];
}

int main() {
  unsigned int x = nondet_uint();
  __CPROVER_assume(x >= 0 && x <= UINT_MAX);
  unsigned int res_ref = count_bits_ref(x);
  unsigned int res_bit = lookup_table_count_bits(x);
  __CPROVER_assert(
      res_ref == res_bit,
      "reference implementation count_bits_ref returned the same value as the "
      "bit-twiddling version lookup_table_count_bits");
}
