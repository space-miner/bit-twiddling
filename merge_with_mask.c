unsigned int nondet_uint();

unsigned int merge_with_mask_ref(unsigned int x, unsigned int y,
                                 unsigned int mask) {
  return (x & ~mask) | (y & mask);
}

unsigned int merge_with_mask_bit(unsigned int x, unsigned int y,
                                 unsigned int mask) {
  return (x & ~mask) | (y & mask);
}

int main() {
  unsigned int x = nondet_uint();
  unsigned int y = nondet_uint();
  unsigned int mask = nondet_uint();
  unsigned int res_ref = merge_with_mask_ref(x, y, mask);
  unsigned int res_bit = merge_with_mask_bit(x, y, mask);
  __CPROVER_assert(merge_with_mask_ref == merge_with_mask_bit,
                   "Err: merge_with_mask_bit did not return the same value as "
                   "merge_with_mask_ref");
}
