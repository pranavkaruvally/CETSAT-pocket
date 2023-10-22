#include <stdio.h>

#include "../data_structures/deque.c"

void zero_stuffing(struct deque* in) {
  while (in->size % 8 != 0) {
    in->insert_rear(in, 0);
  }
}

void print_vector(struct deque* in) {
  for (int i = 0; i < in->size; i++) {
    printf("%d ", in->queue[i]);
  }
  printf("\n");
}

struct deque number_to_deque_bool(const long int input, const unsigned int length) {
  struct deque out = initialise_deque(64);
  for (unsigned int i = 0; (i < length) && (i < 32); i++) {
    out.insert_front(&out, (input >> 1) & 1);
  }
  if (length > 32) {
    for (unsigned int i=32; i < length; i++) {
      out.insert_front(&out, 0);
    }
  }

  return out;
}

long int deque_bool_to_number(const struct deque* input) {
  long int output = 0;
  unsigned int bit_shift = 0;
  long int one = 1;

  for (int i=0; i < input->size; i++, bit_shift += 1) {
    if (input->queue[i]) {
      output |= one << bit_shift;
    }
  }

  return output;
}

size_t divide_up(size_t dividend, size_t divisor) {
  //Error control for zero division is yet to be implemented
  return (dividend + divisor - 1) / divisor;
}


