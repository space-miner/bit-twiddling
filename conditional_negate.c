#include <stdbool.h>

int nondet_int();
bool nondet_bool();

// bool fNegate;  // Flag indicating if we should negate v.
// int x;         // Input value to negate if fNegate is true.
// int r;         // result = fNegate ? -v : v;

int conditional_negate_ref(bool fNegate, int x) { return fNegate ? -x : x; }

int conditional_negate_bit(bool fNegate, int x) {
  return (x ^ -fNegate) + fNegate;
}

int main() {
  int x = nondet_int();
  bool fNegate = nondet_bool();
  unsigned int res_ref = conditional_negate_ref(fNegate, x);
  unsigned int res_bit = conditional_negate_bit(fNegate, x);
  __CPROVER_assert(
      res_ref == res_bit,
      "reference implementation conditional_negate_ref returned the same value "
      "as the bit-twiddling version conditional_negate_bit");
}
