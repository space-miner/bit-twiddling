#include <assert.h>
#include <stdio.h>

int nondet_int();
unsigned int nondet_uint();

#define SWAP(a, b) (((a) == (b)) || (((a) ^= (b)), ((b) ^= (a)), ((a) ^= (b))))

int main() {
  // swapping int values
  {
    int x = nondet_int(), y = nondet_int();
    int a = x, b = y;
    SWAP(a, b);
    __CPROVER_assert(a == y && b == x, "int values are correctly swapped");
  }

  // swapping unsigned int values
  {
    unsigned int x = nondet_uint(), y = nondet_uint();
    unsigned int a = x, b = y;
    SWAP(a, b);
    __CPROVER_assert(a == y && b == x,
                     "unsigned int values are correctly swapped");
  }
}
