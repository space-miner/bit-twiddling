#include <stdbool.h>

unsigned int nondet_uint();

// this implementation could not be verified by cbmc
// bool power_of_2_ref (int x) {
//   while (x > 1 && x % 2 == 0) {
//     x /= 2;
//   }
//   return x == 1;
// }

bool power_of_2_ref(unsigned int x) {
  int ones = 0;
  for (int i = 0; i < sizeof(int) * 8; i++) {
    ones += (x & 1);
    x >>= 1;
  }
  return ones == 1;
}

bool power_of_2_bit(unsigned int x) { return x && !(x & (x - 1)); }

int main() {
  unsigned int x = nondet_uint();
  bool res_ref = power_of_2_ref(x);
  bool res_bit = power_of_2_bit(x);
  __CPROVER_assert(res_ref == res_bit,
                   "reference implementation power_of_2_ref returned the same "
                   "value as the bit-twiddling version power_of_2_bit");
}
