#include <limits.h>
#include <stdbool.h>

int set_or_clear_ref(bool cond, int mask, int word) {
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
  int mask = nondet_int();
  int word = nondet_int();
  int res_ref = set_or_clear_ref(cond, mask, word);
  int res_bit = set_or_clear_bit(cond, mask, word);
  CPROVER_assert(res_ref == res_bit, "Err: set_or_clear_bit did not return the "
                                     "same value as set_or_clear_ref");
}
