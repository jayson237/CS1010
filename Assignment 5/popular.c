/**
 * CS1010 Semester 1 AY22/23
 * Assignment 5: Popular
 *
 * @file: popular.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"

/** 
 * Using a jagged array, the user inputs the number of people and the 2D array.
 * To find the most popular person in the group, the function loops through every
 * row and column to count the char '1' as one friend, and prints out the most 
 * number of friends as well as which column (person) has the most friends.
 *
 * @param[in] input A 2D array that stores the inputs of the user
 * @param[in,out] friend_counter A 1D array which counts and stores the number of 
 * friends each person has
 * @param[in] num_people The number of people
 */

void most_popular(char **input, long *friend_counter, size_t num_people) {
  long friends = 0;
  long most_numof_friends = 0;
  size_t popular = 0;

  for (size_t i = 1; i < num_people; i += 1) {
    for (size_t j = 0; j < i; j += 1) {
      if (input[i][j] == '1') {
        friend_counter[j] += 1;
        friends += 1;
      }
    }
    friend_counter[i] += friends;
    friends = 0;
  }
  
  for (size_t i = 0; i < num_people; i += 1) {
    if (friend_counter[i] > most_numof_friends) {
      most_numof_friends = friend_counter[i];
      popular = i;
    }
  }
  cs1010_println_size_t(popular);
  cs1010_println_long(most_numof_friends);
}



int main() {
  size_t num_people = cs1010_read_size_t();
  long *friend_counter = calloc(num_people, sizeof(long));

  if (friend_counter == NULL) {
    cs1010_println_string("Error");
    return 1;
  }
  
  char **input = cs1010_read_word_array(num_people);
  
  most_popular(input, friend_counter, num_people);

  for (size_t i = 0; i < num_people; i += 1) {
    free(input[i]);
  }

  free(input);
  free(friend_counter);
  input = NULL;
  friend_counter = NULL;
}
