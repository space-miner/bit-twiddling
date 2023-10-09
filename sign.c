#include <limits.h>
#include <stdbool.h>

int nondet_int();

bool sign_ref(int x) {
  if (x < 0) {
    return -1;
  } else if (x > 0) {
    return 1;
  } else {
    return 0;
  }
}

bool sign_bit(int x) {
  return (x != 0) | (x >> (sizeof(int) * CHAR_BIT - 1)); // -1, 0, or +1
}

int main() {
  int x = nondet_int();
  bool res_ref = sign_ref(x);
  bool res_bit = sign_bit(x);
  __CPROVER_assert(res_ref == res_bit,
                   "Err: sign_bit did not return the same value as sign_ref");
}
