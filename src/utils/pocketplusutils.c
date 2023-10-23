#include <stdio.h>
#include <string.h>

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

struct deque* number_to_deque_bool(const long int input, const unsigned int length) {
  struct deque* out = initialize_deque(64);
  for (unsigned int i = 0; (i < length) && (i < 32); i++) {
    out->insert_front(out, (input >> 1) & 1);
  }
  if (length > 32) {
    for (unsigned int i=32; i < length; i++) {
      out->insert_front(out, 0);
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

char* bool_to_string(const struct deque* boolvector) {
  int n = divide_up(boolvector->size, 8);
  char* ret = calloc(n, 0);

  int counter = 0;
  int out = n - 1;
  int shift = 0;

  for (int i = boolvector->size - 1; i >= 0; i--) {
    ret[out] |= (boolvector->queue[i]) << shift;
    if (++shift == 8) {
      ++out;
      shift = 0;
    }
    counter++;
  }
  return ret;
}

void write_bool_deque_to_file(const char* file_name, const struct deque* in) {
  FILE* output_file = fopen(file_name, "wb");
  if (output_file == NULL) {
    //Write debugging message for failure of opening
    return;
  }

  char* bool_string_to_write = bool_to_string(in);
  fprintf(output_file, "%s", bool_string_to_write);
  fclose(output_file);
}

struct deque* read_bool_deque_from_file(const char* file_name) {
  FILE* input_file = fopen(file_name, "rb");
  if (input_file == NULL) {
    //Write debugging message for failure of opening 
    exit(1);
  }

  char buffer_char[64];
  fgets(buffer_char, 64, input_file);
  int string_length = strlen(buffer_char);
  struct deque* buffer_bool = initialize_deque(string_length);

  for (int c=0; c < string_length; c++) {
    for (int i=0; i < 8; i++) {
      buffer_bool->insert_front(
        buffer_bool,
        ((unsigned char)(buffer_char[c]) >> i) & 1
      );
    }
  }
  return buffer_bool;
}

void pop_n_from_front(struct deque* in, const unsigned int n) {
  if (in->size > 0) {
    //Throw not enough elements Error
    return;
  }
  for (unsigned int i = 0; i < n; i++) {
    if (in->size > 0) {
      in->delete_front(in);
    } else {
      i = n;
    }
  }
}
