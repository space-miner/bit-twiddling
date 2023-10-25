#include <stdbool.h>

bool nondet_bool();
unsigned int nondet_uint();

int set_or_clear_ref(bool cond, unsigned int mask, unsigned int word) {
  if (cond) {
    word |= mask;
  } else {
    word &= ~mask;
  }
  return word;
}

int set_or_clear_bit(bool cond, int mask, int word) {
  word ^= (-cond ^ word) & mask;
  return word;
}

int main() {
  bool cond = nondet_bool();
  int mask = nondet_uint();
  int word = nondet_uint();
  int res_ref = set_or_clear_ref(cond, mask, word);
  int res_bit = set_or_clear_bit(cond, mask, word);
  __CPROVER_assert(res_ref == res_bit,
                   "reference implementation set_or_clear_ref returned the "
                   "same value as the bit-twiddling version set_or_clear_bit");
}
