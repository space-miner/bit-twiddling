#include <stdbool.h>

bool diff_signs_ref(int x, int y) {
  if (x < 0 && y >= 0) {
    return true;
  } else if (y < 0 && x >= 0) {
    return true;
  } else {
    return false;
  }
}

bool diff_signs_bit(int x, int y) {
  bool res = (x ^ y) < 0;
  return res;
}

int main() {
  int x = nondet_int();
  int y = nondet_int();
  int res_ref = diff_signs_ref(x, y);
  int res_bit = diff_signs_bit(x, y);
  CPROVER_assert(res_ref == res_bit, "Err: diff_signs_bit did not return the same value as diff_signs_ref");
}
