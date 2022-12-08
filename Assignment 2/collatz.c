/**
 * CS1010 Semester 1 AY22/23
 * Assignment 2: Collatz 
 *
 * @file: collatz.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"
#include <math.h>

long calculate_stops (long initial) {
  long stops = 0;
  while (initial!=1) {
    if (initial%2 == 0) {
      initial = initial/2;
    } else {
      initial = 3*initial + 1;
    }
    stops+=1;
  }
  return stops;
}


void compare_most_stops (long m,long n) {
  long max_stops;
  long number_max;
  long current_max = 0;
  while (m<=n) {
    if (calculate_stops(m) >= current_max) {
      number_max = m;
      max_stops = calculate_stops(m);
      current_max = calculate_stops(m);
    }
    m+=1;
  }
  cs1010_println_long(max_stops);
  cs1010_println_long(number_max);
}


int main() {
  long m = cs1010_read_long();
  long n = cs1010_read_long();
  compare_most_stops(m,n);
}



