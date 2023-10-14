unsigned int nondet_uint();

// unsigned int x;    // value to merge in non-masked bits
// unsigned int y;    // value to merge in masked bits
// unsigned int mask; // 1 where bits from y should be selected; 0 where from x.
// unsigned int r;    // result of (x & ~mask) | (y & mask) goes here

unsigned int merge_with_mask_ref(unsigned int x, unsigned int y,
                                 unsigned int mask) {
  return (x & ~mask) | (y & mask);
}

unsigned int merge_with_mask_bit(unsigned int x, unsigned int y,
                                 unsigned int mask) {
  return x ^ ((x ^ y) & mask);
}

int main() {
  unsigned int x = nondet_uint();
  unsigned int y = nondet_uint();
  unsigned int mask = nondet_uint();
  __CPROVER_assume(mask == 0 || mask == 1);
  unsigned int res_ref = merge_with_mask_ref(x, y, mask);
  unsigned int res_bit = merge_with_mask_bit(x, y, mask);
  __CPROVER_assert(merge_with_mask_ref == merge_with_mask_bit,
                   "Err: merge_with_mask_bit did not return the same value as "
                   "merge_with_mask_ref");
}
