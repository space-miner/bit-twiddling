unsigned int nondet_uint();

unsigned int naive_count_bits_ref(unsigned int x) {
  unsigned int c;
  for (int i = 0; i < sizeof(unsigned int) * 8; i++) {
    c += x & 1;
    x >>= 1;
  }
  return c;
}

unsigned int naive_count_bits_bit(unsigned int x) {
  unsigned int c;
  for (c = 0; x; x >>= 1) {
    c += x & 1;
  }
  return c;
}

int main() {
  unsigned int x = nondet_uint();
  unsigned int res_ref = naive_count_bits_ref(x);
  unsigned int res_bit = naive_count_bits_bit(x);
  __CPROVER_assert(res_ref = res_bit,
                   "Err: naive_count_bits_bit did not return the same value as "
                   "naive_count_bits_ref");
}
