/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: Max
 *
 * Read in a sequence of numbers and recursively find
 * the maximum.
 *
 * @file: max.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"
long find_max(const long list[], long start, long end) {
  if (start != 0 && start == end) {
    return list[start-1];
  } 
  if (start == end) {
    return list[start];
  }

  long middle = (start+end)/2;
  long first_half = find_max(list, start, middle);
  long second_half = find_max(list, middle+1, end);

  if (second_half > first_half) {
    return second_half;
  }
  return first_half;
}

int main() {
  long list[100000];
  long num_of_elems = cs1010_read_long();
  for (long i = 0; i < num_of_elems; i += 1) {
    list[i] = cs1010_read_long();
  }

  cs1010_println_long(find_max(list, 0, num_of_elems));
}
