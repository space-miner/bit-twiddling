#include <stdbool.h>

// this implementation could not be verified by cbmc
// bool pow2_ref (int x) {
//   while (x > 1 && x % 2 == 0) {
//     x = x/2;
//   }
//   return x == 1;
// }

bool pow2_ref (int x) {
  int ones = 0;
    for (int i = 0; i < sizeof(int); i++) {
        ones += (x & 1);
        x >>= 1;
    }
    return ones == 1;
}

bool pow2_bit (int x) {
  return x && !(x & (x - 1));
}

int main() {
    int x = nondet_int();
    int res_ref = pow2_ref(x);
    int res_bit = pow2_bit(x);
    CPROVER_assert(res_ref == res_bit, "Err: pow2_bit did not return the same value as pow2_ref");
}
