/*
 * CS1010 Semester 1 AY22/23
 * Assignment 4: Kendall
 *
 * Read in a sequence of numbers and find its kendall tau 
 * distance.
 *
 * @file: kendall.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"

/**
 * Find the possible combination of normalized kendall pairs from the list inserted by user 
 * based on their ranking, and calculate the ratio towards all possible combination.
 *
 * @param[in] size The maximum size for the long array 
 * @param[in] list A long-type array that stores in the value of inputs
 * 
 * Prints the probability of kendall pairs out of all combination
 */

void compute_kendall (long *list, size_t size) {
  long count_kendall = 0;
  for (size_t i = 0; i < size; i += 1) {
    for(size_t j = i+1; j < size; j += 1) {
      if (list[i] > list[j]) {
        count_kendall += 1;
      }
    }
  }
  double total_combination = (double)(size * (size - 1)) / 2;
  double answer = (double)count_kendall/total_combination;
  cs1010_println_double(answer);
}


int main() {
  size_t size = cs1010_read_size_t();
  long *list = cs1010_read_long_array(size);
  compute_kendall(list, size);
  free(list);
  list = NULL;
}
