/**
 * CS1010 Semester 1 AY22/23
 * Assignment 3: Days
 *
 * @file: days.c
 * @author: 
 */

#include "cs1010.h"


void compute_day(long month, long date) {
  long num_of_days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  long x = 1;
  long total_days = 0;
  long answer;
  while(x<month) {
    total_days += (num_of_days[x-1]);
    x+=1;
  }
  answer = total_days + date;
  cs1010_println_long(answer);
}


int main() {
  long month = cs1010_read_long();
  long date = cs1010_read_long();
  compute_day(month, date);
}
