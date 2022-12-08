/**
 * CS1010 Semester 1 AY22/23
 * Assignment 2: Pattern
 *
 * @file: pattern.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"
#include <math.h>
#include <stdbool.h>

long lead_cell_num (long interval, long height) {
  long lead = 1;
  for (long row = 1; row < height; row+=1) {
    lead = lead + (interval*(row));
  }
  return lead;
}

bool is_prime(long number) {
  for (long x = 2; x*x <= number; x+=1) {
    if ((number%x == 0) && (number!=2)) {
      return false;
    } 
  }
  return true;
}


bool is_cell_prime(long interval, long height, long first_num, long column) {
  long number = 0;
  number = column + first_num;
  if (interval == 1) {
    return false;
  }
  for (long x = 1; x <= interval; x+=1) {
    if (is_prime(number) == true) {
      return true;
    }
    number+=height; 
  }
  return false;
}


void print_blank (long blank) {
  for (long x = 1; x <= blank; x+=1) {
    cs1010_print_string(" ");
  }
}


void draw_pyramid(long interval, long height) {
  long first_num;
  bool check_prime;
  long column = (2*height)-1;
  long blank = height-1; 

  for (long row = 1; row <= height; row+=1) {
    print_blank(blank);
    first_num = lead_cell_num(interval,row);
    for (long verti = 1;  verti <= (column-(2*blank)); verti+=1) {
      check_prime = is_cell_prime(interval,row,first_num,verti-1);
      if (check_prime == true) {
        cs1010_print_string("#");
      } else {
        cs1010_print_string(".");
      }
    }
    print_blank(blank);
    blank-=1;
    cs1010_println_string("");
  }
}


int main() {
  long m = cs1010_read_long(); //interval
  long h = cs1010_read_long(); //height
  draw_pyramid(m,h);
}
