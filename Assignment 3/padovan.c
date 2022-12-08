/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: Padovan
 *
 * @file: padovan.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"
void write_padovan(long number) {
  long padovan[161];
  padovan[0] = 1;
  padovan[1] = 0;
  padovan[2] = 0;
  for (long x = 3; x <= number; x+=1) {
    padovan[x] = padovan[x-2]+padovan[x-3];
  }

  for (long x = number; x >= 0; x-=1) {
    cs1010_println_long(padovan[x]);
  }
}


int main() {
  long number = cs1010_read_long();
  write_padovan(number);
}

