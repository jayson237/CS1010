/**
 * CS1010 Semester 1 AY22/23
 * Assignment 5: Social
 *
 * @file: social.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"

#define FRIEND '1'
#define STRANGER '0'

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

char sort(char **input, size_t j, size_t k) {
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

bool is_direct(char **input, size_t j, size_t k) {
  if (sort(input,j,k) == FRIEND) {
    return true;
  }
  return false;
}

/**
 * The function has the responsibility to check whether two people has an 
 * indirect contact through a third person
 *
 * @param[in] input A 2D array that stores the jagged array inserted by an user 
 * @param[in] num_people The number of person limited by the user
 * @param[in] j A person whose contact number is stored in row j and column j
 * @param[in] k A person whose contact number is stored in row k and column k
 * 
 * @return Returns true if there is an indirect contact with a third person,
 * false otherwise
 */

bool is_indirect(char **input, size_t num_people, size_t j, size_t k) {
  bool condition = false;
  for (size_t i = 0; !condition && i < num_people; i += 1) {
    if (sort(input,i,j) == FRIEND && sort(input,i,k) == FRIEND) {
      condition = true;
    }
  }
  return condition;
}

/** 
 * Copying the values stored from input into a new calloc list
 *
 * @param[in,out] input A 2D array that stores the jagged array inserted by an user
 * @param[in] n The number of person limited by the user
 *
 * @return The brand new array that has copied values from input
 */

char **copy_input(char **input, size_t n) {
  char **copy = calloc(n, sizeof (char *));
  if (copy == NULL) {
    cs1010_println_string("Error");
    return (char**) 1;
  }
   
  for (size_t i = 0; i < n; i += 1) {
    copy[i] = calloc(i + 1, sizeof(char));
    if (copy[i] == NULL) {
      cs1010_println_string("Error");
      for (size_t j = 0; j <= i; j += 1) {
        free(copy[j]);
      }
      free(copy);
      return (char**) 1;
    }
  }

  for (size_t i = 0; i < n; i += 1) {
    for (size_t j = 0; j <= i; j += 1) {
      copy[i][j] = input[i][j];
    }
  }
  return copy;
}


/**
 * To change '0' to '1' if two person does not have any direct contact and an indirect
 * contact instead
 *
 * @param[in,out] input A 2D Array that stores and updates the values inserted by the user
 * @param[in] n The number of person limited by the user
 *
 * @return The updates input array
 */

char **social(char **input, size_t n) {
  char **copy = copy_input(input,n);
  for (size_t i = 1; i < n; i += 1) {
    for (size_t j = 0; j < i; j += 1) {
      if (copy[i][j] == STRANGER && is_indirect(copy,n,i,j) == true) {
        input[i][j] = FRIEND;
      }
    }
  }

  for (size_t i = 0; i < n; i += 1) {
    free(copy[i]);
  }
  free(copy);
  copy = NULL;
  return input;
}


/**
 * A recursion function to loop k degrees(hops) and calls social to check
 * whether a person is indirectly connected to one another through a third person
 *
 * @param[in,out] input A 2D array that stores and updates the brand new list for output
 * @param[in] n The number of person limited by the user
 * @param[in,out] k The chain degree
 *
 * @return The updates input list
 */

char **get_next(char **input, size_t n, size_t k) {
  if (k == 1) {
    return input;
  }
  return get_next(social(input,n), n, k-1);
}


int main() {
  size_t num_people = cs1010_read_size_t();
  size_t degree = cs1010_read_size_t();
  char **input  = cs1010_read_word_array(num_people);
  char **copy   = get_next(input, num_people, degree);
   
  for (size_t i = 0; i < num_people; i += 1) {
    for (size_t j = 0; j <= i; j += 1) {
      putchar(copy[i][j]);
    }
    cs1010_println_string("");
  }
  
  for (size_t i = 0; i < num_people; i += 1) {
    free(input[i]);
  }

  free(input);
  input = NULL;
}
