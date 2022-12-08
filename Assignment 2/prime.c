/**
 * CS1010 Semester 1 AY22/23
 * Assignment 2: Prime
 *
 * @file: prime.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

bool is_prime(long input) {
  for (long i = 2; i*i <= input; i+=1) {
    if ((input%i == 0) && (input!=2)) {
      return false;
    } 
  }
  return true;
}


void largest_prime(long input) {
  long condition = 0;
  while (condition == 0) {
    if (is_prime(input) == true) {
      cs1010_println_long(input);
      condition+=1;
    } 
    input-=1;
  }
}


int main() {
  long n = cs1010_read_long(); //input
  largest_prime(n);
}
