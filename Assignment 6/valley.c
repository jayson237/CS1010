/**
 * CS1010 Semester 1 AY22/23
 * Assignment 6: Valley
 *
 * @file: valley.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"

/**
 * To find the minimal value given by the user, the function
 * takes in the list as well as the length of the array. By 
 * first identifying the midpoint of the v-array, the function 
 * goes through every iteration to check which is the smallest
 * number accordingly to the conditions below.
 *
 * @param[in,out] list The array that stores in a number of values
 * @param[in] len The length of the array
 *
 * @return Returns the midpoint value accordingly
 * to its condition. Otherwise, 0.
 */

long find_min(long *list, long len) {
  if (len == 1) {
    return list[0];
  }
  
  long start = 0;
  long end = len - 1;
  while (start <= end) {
    long mid = (start + end)/2;

    if (mid == 0 && list[mid] < list[mid+1]) {
        return list[mid];
    }

    if (mid == len - 1 && list[mid] < list[mid-1]) {
        return list[mid];
    }
    
    if (list[mid] < list[mid-1] && list[mid] < list[mid+1]) {
        return list[mid];
    }

    if (list[mid+1] >= list[mid]) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return 0;

}


int main() {
  long len = cs1010_read_long();
  long *input = calloc((size_t)len, sizeof(long));
  for(long i = 0; i < len; i += 1) {
    input[i] = cs1010_read_long();
  }

  cs1010_println_long(find_min(input,len));

  free(input);
  input = NULL;
}
