/**
 * CS1010 Semester 1 AY22/23
 * Assignment 6: Sort
 *
 * @file: sort.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"

/**
 * To find the index where the array is split into 2 sections, one non-ascending
 * and the other non_descending
 *
 * @param[in] list The list of numbers to be sorted
 * @param[in] len The length of the array
 *
 * @return the index between two segments
 */

long find_index_between_segments(long *list, long len) {
  long mid = 0;
  while (mid < len && list[mid] >= list[mid+1]) {
    mid += 1; 
  }
  return mid;
}


/**
 * To sort the list by comparing the value between the non-ascending and
 * non-descending. If there is no longer any value on either side of the
 * segment, the function prints the remaining numbers accordingly to ascend
 * them in order
 *
 * @param[in,out] list The list of numbers to be sorted
 * @param[in] len The length of the array
 *
 * prints out the sorted numbers
 */

void sort(long *list, long len) {
  long mid = find_index_between_segments(list, len);
  cs1010_println_long(list[mid]);

  
  long start = mid - 1;
  long end = mid + 1;
  while (start >= 0 && end < len) {
    if (list[start] <= list[end]) {
      cs1010_println_long(list[start]);
      start -= 1;
    } else {
      cs1010_println_long(list[end]);
      end += 1;
    }
  }
  

  if (start < 0) {
    for (long i = end; i < len; i += 1) {
      cs1010_println_long(list[i]);
    }
  } else {
    for (long i = start; i >= 0; i -= 1) {
      cs1010_println_long(list[i]);
    }
  }
}


int main() {
  long len = cs1010_read_long();
  long *list = calloc((size_t)len, sizeof (long));
  for (long i = 0; i < len; i += 1) {
    list[i] = cs1010_read_long();
  }

  if (len == 1) {
    cs1010_println_long(list[0]);
  } else {
    sort(list,len);
  }

  free(list);
  list = NULL;
}
