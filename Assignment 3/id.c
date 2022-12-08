/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: ID
 *
 * @file: id.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"

void check_code(long number) {
  char list_code[13] = { 'Y', 'X', 'W', 'U', 'R', 'N', 'M', 'L', 'J', 'H', 'E', 'A', 'B'};
  long sum = 0;
  long remainder;
  for (long i = number; i > 0; i = i/10) {
    sum = sum + (i%10);
    remainder = sum%13;
  }
  putchar(list_code[remainder]);
}


int main() {
  long id = cs1010_read_long();
  check_code(id);  
}
