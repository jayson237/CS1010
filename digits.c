/**
 * CS1010 Semester 1 AY22/23
 * Assignment 1: Digits
 *
 * Read in a positive integer from the standard input and print
 * the sum of its digits to the standard output.
 *
 * @file: digits.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"

long sum_of_digits_cubed(long input){
  long digit = input%10;
  long sum_cubed = digit*digit*digit;
  if (input>0){
    return sum_cubed + sum_of_digits_cubed(input/10);
  } return 0;
}


int main()
{
 long input = cs1010_read_long();
 cs1010_println_long(sum_of_digits_cubed(input));
}
