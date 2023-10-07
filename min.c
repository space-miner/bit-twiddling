int min_ref(int x, int y) {
  if (x <= y) {
    return x;
  } else {
    return y;
  }
}

int min_bit(int x, int y) { return y ^ ((x ^ y) & -(x < y)); }

int main() {
  int x = nondet_int();
  int y = nondet_int();
  int res_ref = min_ref(x, y);
  int res_bit = min_bit(x, y);
  CPROVER_assert(res_ref == res_bit,
                 "Err: min_bit did not return the same value as min_ref");
}
