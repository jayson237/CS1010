/**
 * CS1010 Semester 1 AY22/23
 * Assignment 6: Lexicon
 *
* @file: lexicon.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"
#include <string.h>

/**
 * To find the longest length out of all words inserted by user
 *
 * @param[in] input A 2D array that store characters set by the user
 * @param[in] len The number of words 
 *
 * @return the number of digits possess by the longest element
 */

long find_longest_str(char **input, long len) {
  long m;
  for (long i = 0; i < len-1; i += 1) {
    if (strlen(input[i]) > strlen(input[i+1])) {
      m = (long)strlen(input[i]);
    } else {
      m = (long)strlen(input[i+1]);
    }
  }
  return m;
}

/**
 * To sort the list with a similar method to counting sort, but this time
 * with a time complexity of O(m(n+k)). By comaparing and considering the 
 * ASCII code as well as the length of every integers, the new list of lengths
 * and sorted index list will be updated after every iteration from m - 1 to 0
 * 
 * @param[in,out] input The 2D array that stores in characters and print them accordingly to lexicographical order
 * @param[out] sorted An array that updates the index list in radix sort
 * @param[in,out] index_list The list of indexes that will be updated with the sorted indexes after every radix sort function call
 * @param[in,out] str_len The list of lengths of every iteration
 * @param[out] new_len To store new list of lengths for str_len
 * @param[in] len The number of words
 * @param[in,out] curr_col The current column that is being checked
 *
 */

void radix_sort(char **input, long *sorted, long *index_list, long *str_len, long *new_len, long len, long curr_col) {
  long counter[95] = {0};
  counter[0] = 0;
  long position = 0;
  long symbol_index = 0;
    
  for (long i = 0; i < len; i += 1) {
    position = index_list[i];
    if (str_len[i] <= curr_col) {
      counter[0] += 1; //NULL
    } else {
      symbol_index = (long)input[position][curr_col] - 32;
      counter[symbol_index] += 1;
    }
  }

  for (long i = 1; i < 95; i += 1) {
    counter[i] += counter[i - 1];
  }

  for (long i = len - 1; i >= 0; i -= 1) {
    position = index_list[i];
    
    if (str_len[i] <= curr_col) {
      sorted[counter[0] - 1] = index_list[i];
      new_len[counter[0] - 1] = str_len[i];
      counter[0] -= 1;
    } else {
      symbol_index = (long)input[position][curr_col] - 32;
      sorted[counter[symbol_index] - 1] = index_list[i];
      new_len[counter[symbol_index] - 1] = str_len[i];
      counter[symbol_index] -= 1;
    }
  }

  //UPDATE
  for (long i = 0; i < len; i += 1) {
    index_list[i] = sorted[i];
    str_len[i] = new_len[i];
  }
}


/**
 * To do sorting by first setting up the length of the original strings
 * and indexes. On top of that, checking and sorting from the right column to
 * the left. In the end, printing the character in lexicographical order
 *
 * @param[in,out] input The 2D array that stores in characters and print them accordingly to lexicographical order
 * @param[out] sorted An array that updates the index list in radix sort
 * @param[in,out] str_len The list of lengths of every iteration
 * @param[out] new_len To store new list of lengths for str_len
 * @param[in] len The number of words
 */

void do_sort(char **input, long *sorted, long *str_len, long *new_len, long len) {
  long m = find_longest_str(input,len);
  long *index_list = calloc((size_t)len, sizeof(long));
  //Initial Lengths
  for (long i = 0; i < len; i += 1) {
    str_len[i] = (long)strlen(input[i]);
  }
  
  for (long i = 0; i < len; i += 1) {
    index_list[i] = i;
  }

  for (long i = m - 1; i >= 0; i -= 1) {
    radix_sort(input, sorted, index_list, str_len, new_len, len, i);
  }

  for (long i = 0; i < len; i += 1) {
    cs1010_println_string(input[index_list[i]]);
  }

  free(index_list);
  index_list = NULL;
}


int main() {
  long n = cs1010_read_long();
  char **input = cs1010_read_word_array((size_t)n);
  long *sorted = calloc((size_t) n, sizeof(long)); 
  long *str_len = calloc((size_t) n, sizeof(long));
  long *new_len = calloc((size_t) n, sizeof(long)); 
  
  do_sort(input,sorted,str_len,new_len,n);
  
  for (long i = 0; i < n; i += 1) {
    free(input[i]);
  }
  free(input);
  free(sorted);
  free(str_len);
  free(new_len);
  input = NULL;
  sorted = NULL;
  str_len = NULL;
  new_len = NULL;
}
