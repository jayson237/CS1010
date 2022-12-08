/**
 * CS1010 Semester 1 AY22/23
 * Assignment 4: Subtract
 *
 * @file: subtract.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"
#include <string.h>

/**
 * One of the subtraction methods, which borrows the digit before the currrent
 * number in array 'a' if the current digit is smaller then the current digit
 * in array 'b'. In the case of digit '0', the digit would be changed to 9
 * and recursively calling the digit before that, otherwise,it would be
 * minus one integer everytime if the function is called.
 *
 * @param[in,out] a The current digit of char a when current digit of a is smaller than
 * current digit of b
 * @param[in] size The maximum size of the array a
 *
 * @return Returns the new array for a to be subtracted with array b
 */

char *borrow (char *a, size_t size) {
  size_t i = size - 1;
  if (a[i] != '0') {
    a[i] = ((a[i] -'0') - ('1' - '0')) + '0';
  } else {
    a[i] = '9';
    borrow(a, i);
  }
  return a;
}

/**
 * Check if a is equals to b in terms of number
 *
 * @param[in] a An array that stores the characters (first number) inputted by user
 * @param[in] b An array that stores the second number in characters
 *
 * @return Returns true if both numbers have the same length and characters,
 * otherwise, returns false.
 */

bool is_equal (char *a, char *b) {
  size_t len_a = strlen(a); 
  size_t len_b = strlen(b);
  if (len_a != len_b) {
    return false;
  }

  for (size_t i = 0; i < len_a; i += 1) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

/**
 * By subtracting, the function has to take into account both character lists and allocating a new
 * malloc or calloc character array. As the trivial condition, if a = b, then array will automatically 
 * be 0. Otherwise, the function loops from the right of the lists and compare the current digit of a to b.
 * if a < b, the borrow function will be called and the new current digit of 'a' is added 10,then subtracted 
 * against the current digit of b. Or else, the program will subtract normally according to the laws of string
 *
 * @param[in,out] a A list of char numbers that will be subtracted against char numbers of b
 * @param[in] b An array for the second input
 *
 * @return Returns the product of subtraction in the form of array
 *
 * @pre assume a > b in terms of integer or long
 */

char *subtract (char *a, char *b) {
  size_t len_a = strlen(a);
  size_t len_b = strlen(b);
  char *array = calloc(len_a + 1, sizeof(char));

  if (is_equal(a,b)) {
    array[0] = '0';
    array[1] = '\0';
    return array;
  }


  for (size_t i = 1; i <= len_b; i += 1) {
    if ((a[len_a - i] - '0') < (b[len_b - i] - '0')) {
      borrow(a, len_a - i);
      a[len_a - i] = ((a[len_a - i] - '0') + 10 - (b[len_b - i] - '0')) + '0';
    } else {
      a[len_a - i] = ((a[len_a - i] - '0')  - (b[len_b - i] - '0')) + '0';
    }
  }
  
  //For answers with leading zeros excluding 0
  size_t leading_zeros = 0;
  size_t i = 0;
  while (a[i] == '0') {
    leading_zeros += 1;
    i += 1;
  }

  for (size_t j = leading_zeros; j < len_a; j += 1) {
    array[j - leading_zeros] = a[j];
  }

  array[len_a - leading_zeros] = '\0';
  return array;
}


int main() {
  char *a = cs1010_read_word();
  char *b = cs1010_read_word();
  char *answer = subtract(a,b);
  cs1010_println_string(answer);
  free(a);
  free(b);
  free(answer);
  a = NULL;
  b = NULL;
  answer = NULL;
}
