#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

void zero_stuffing(bool** in);
void print_vector(const bool** in);
bool* number_to_deque_bool(const long int* input, const unsigned int* length);
long int* deque_bool_to_number(const bool** input);
size_t divide_up(size_t dividend, size_t divisor);
char* bool_to_string(const bool* boolvector);
void write_bool_deque_to_file(const char* file_name, const bool** in);
bool* read_bool_deque_from_file(const char** filename);
void pop_n_from_front(bool** in, const unsigned int* n);

#endif
