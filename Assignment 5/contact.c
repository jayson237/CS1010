/**
 * CS1010 Semester 1 AY22/23
 * Assignment 5: Contact
 *
 * @file: contact.c
 * @author: Jayson Ng (Group E03)
 */


#include "cs1010.h"
#include <stdbool.h>

/**
 * To sort the numbers around in case the number of 
 * row and/or column is j < k
 *
 * @param[in,out] input A 2D array that stores the jagged array inputs of an user
 * @param[in,out] j A person whose contact number is stored in row j and column j
 * @param[in,out] k A person whose contact number is stored in row k and column k
 *
 * @return Returns the character of input[j][k] if j < k, otherwise input[k][j]
 */

char sort (char **input, size_t j, size_t k) {
  if (k > j) {
    return input[k][j];
  } 
  return input[j][k];
}

/**
 * To check whether if person j is directly contacted to person k
 * 
 * @param[in] input A 2D array that stores the jagged array inputs of an user
 * @param[in] j A person whose contact number is stored in row j and column j
 * @param[in] k A person whose contact number is stored in row k and column k
 *
 * @return Returns true if j is a friend of k, otherwise false
 */

bool is_friend (char **input, size_t j, size_t k) {
  if (sort(input,j,k) == '1') {
    return true;
  }
  return false;
}

/**
 * If is_friend returns false, the contact_through function will be called
 * and find the location of the common friend and prints it out to the standard
 * out. Otherwise, if no common friend is found function will print "no contact"
 *
 * @param[in,out] input A 2D array that stores the jagged array inputs of an user
 * @param[in] num_people The number of people set by the user  
 * @param[in] j A person whose contact number is stored in row j and column j
 * @param[in] k A person whose contact number is stored in row k and column k 
 */

void contact_through (char **input, size_t num_people, size_t j, size_t k) {
  bool condition = true;

  for (size_t i = 0; condition && i < num_people; i += 1) {
    if (sort(input,j,i) == '1' && sort(input,k,i) == '1') {
      cs1010_print_string("contact through ");
      cs1010_println_size_t(i);
      condition = false;
    }
  }
  if (condition == true) {
    cs1010_println_string("no contact");
  }
}


/**
 * Has the responsibility to print out the relationship between person j and k
 * by checking is_friend or contact_through otherwise
 *
 * @param[in] input A 2D array that stores the jagged array inputs of an user
 * @param[in] num_people The number of people set by the user
 * @param[in] j A person whose contact number is stored in row j and column j
 * @param[in] k A person whose contact number is stored in row k and column k 
 */

void trace_contact (char **input, size_t num_people, size_t j, size_t k) {
  if (is_friend(input,j,k)) {
    cs1010_println_string("direct contact");
  } else {
    contact_through(input, num_people, j, k);
  }
}



int main() {
  size_t num_people = cs1010_read_size_t(); 
  char **input = cs1010_read_word_array(num_people);
  size_t j = cs1010_read_size_t();
  size_t k = cs1010_read_size_t();

  trace_contact(input, num_people, j, k);

  for (size_t i = 0; i < num_people; i += 1) {
    free(input[i]);
  }

  free(input);
  input = NULL;
}
