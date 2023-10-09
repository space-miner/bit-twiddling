int min_ref(int x, int y) {
  if (x <= y) {
    return x;
  } else {
    return y;
  }
}

int min_bit(int x, int y) {
  return y ^ ((x ^ y) & -(x < y)); // min(x, y)
}

int max_ref(int x, int y) {
  if (x <= y) {
    return y;
  } else {
    return x;
  }
}

int max_bit(int x, int y) {
  return x ^ ((x ^ y) & -(x < y)); // max(x, y)
}

int main() {
  int x = nondet_int();
  int y = nondet_int();
  int minimum_ref = min_ref(x, y);
  int minimum_bit = min_bit(x, y);
  int maximum_ref = max_ref(x, y);
  int maximum_bit = max_bit(x, y);
  __CPROVER_assert(minimum_ref == minimum_bit,
                 "Err: min_bit did not return the same value as min_ref");
  __CPROVER_assert(maximum_ref == maximum_bit,
                 "Err: max_bit did not return the same value as max_ref");
}
