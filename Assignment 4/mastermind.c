/**
 * CS1010 Semester 1 AY22/23
 * Assignment 4: Mastermind
 *
 * @file: mastermind.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"

/**
 *   The function black_counter has a responsibility of checking whether the guessing
 *   pin conditions have the exact color and position as the first given code. And for
 *   everytime that it identifies true for both color and position, the counter increments
 *   and resets the value of both lists to 0 to avoid repetition.
 *      
 *   @param[in] guess An array containing the numbers guessed by the user
 *   @param[in] code The array that stores the original numbers for the user to guess
 *   @param[in,out] count_black Counter for how many pins are true for both color and position
 *          
 *   @pre count_black = 0
 */            

void black_counter (long guess[], long code[], long *count_black) {
  for (long x = 0; x < 4; x += 1) {
    if (guess[x] == code[x]) {
      *count_black += 1;
      guess[x] = 0;
      code[x] = 0;
    }
  }
}

/**
 * The function white_counter has a responsibility of checking whether the guessing
 * pin/numbers contain any one of the colors that are set as the guessing code, but not
 * the position. And for everytime it shows true for the condition, the counter increments
 * and also resets the value of both lists to 0.
 *
 * @param[in] guess An array containing the numbers guessed by the user
 * @param[in] code The array that stores the original numbers for the user to guess
 * @param[in,out] count_white Counter for how many pins matched the consisting colors
 *
 * @pre count_white = 0
 */

void white_counter (long guess[], long code[], long *count_white) {
  for (long x = 0; x < 4; x += 1) {
    for (long y = 0; guess[x] != 0 && y < 4; y += 1) {
      if (guess[x] == code[y] && code[y] != 0) {
        *count_white += 1;
        guess[x] = 0;
        code[y] = 0;
      }
    }
  }
}

/**
 * Mastermind is a guessing game whereby the user guesses 4 numbers that corresponds
 * to certain colors by reading the code and guess lists. When it is guessed correctly 
 * or when the black_counter reaches to 4, the program will end (terminate). Otherwise, 
 * the game will continue on and print the corresponding black and white counter based on 
 * the guess made by user until it reaches the termination state.
 *
 * @param[in] code An array that stores the code that consists of 4 numbers for the user to guess
 */


void play_mastermind (const long code[]) {
  long guess[4];
  long check[4];
  long count_black = 0;
  long count_white = 0;
  while (count_black != 4) {
    count_black = 0;
    count_white = 0;
    for (long i = 0; i < 4; i += 1) {
      check[i] = code[i];
    }  

    for (long i = 0; i < 4; i += 1) {
      guess[i] = cs1010_read_long();
    }

    black_counter(guess, check, &count_black);
    if (count_black != 4) {
      white_counter(guess, check, &count_white);
    }
    cs1010_print_long(count_black);
    cs1010_print_string(" ");
    cs1010_println_long(count_white);
  }
}


int main() {
  long code[4];
  for (long i = 0; i < 4; i += 1) {
    code[i] = cs1010_read_long();
  }
  play_mastermind(code);
}
