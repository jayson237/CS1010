/**
 * CS1010 Semester 1 AY22/23
 * Assignment 8: Digits
 *
 * @file: digits.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"
#include <stdbool.h>

#define NCOLS 28
#define NROWS 28
#define WHITE '.'
#define BLACK '#'
#define K 5

typedef struct {
  char **sample;
  long label;
} digit;

typedef struct {
  long neighbor;
  long distance;
} neighbor;


/**
 * To read both training and testing samples in the form of 2D arrays
 *
 * param[in] size The number of rows, in this case 28
 *
 * @return Returns the samples inserted by user
 */
char **read(size_t size) {
  char **sample = calloc(size, sizeof(char *));
  if (sample == NULL) {
    return NULL;
  }
  for (size_t i = 0; i < size; i += 1) {
    sample[i] = cs1010_read_word();
    if (sample[i] == NULL) {
      for (size_t j = 0; j < i; j += 1) {
        free(sample[j]);
      }
      free(sample);
      return NULL;
    }
  }
  return sample;
}


/**
 * To compute how many different pixels are there between a testing case
 * and a training case
 *
 * @param[in] train The training sample
 * @param[in] test The testing sample
 * @param[in] limit The current maximum distance
 *
 * @return Returns -1 if the distance is larger than the limit, otherwise
 * returns the number of different pixels (distance)
 */
long compute_distance(char **train, char **test, long limit) {
  long distance = 0;
  for (size_t i = 0; i < NROWS; i += 1) {
    for (size_t j = 0; j < NCOLS; j += 1) {
      if (limit != -1 && distance > limit) {
        return -1;
      }
      if (test[i][j] != train[i][j]) {
        distance += 1;
      }
    }
  }
  return distance;
}


/**
 * To insert a neighboring digit and the distance into the 'neighbor' struct array
 *
 * @param[in] digit The digit to be inserted
 * @param[in] neighbor A struct array that stores in the digit and distance
 * @param[in] distance The calculated distance
 */
void insert(long digit, neighbor neighbor[K], long distance) {
  long i = 0;
  while (i < K && neighbor[i].distance != -1 && distance > neighbor[i].distance) {
    i += 1;
  }
  while (i < K && distance == neighbor[i].distance && neighbor[i].neighbor < digit) {
    i += 1;
  }
  for (long j = K - 1; j > i; j -= 1) {
    neighbor[j].neighbor = neighbor[j - 1].neighbor;
    neighbor[j].distance = neighbor[j - 1].distance;
  }
  if (i < K) {
    neighbor[i].neighbor = digit;
    neighbor[i].distance = distance;
  }
}


/**
 * To identify which numbers are tested according to the training samples
 *
 * @param[in] neighbor The struct array containing k-nearest neighbors
 *
 * @return Returns the number that the program identifies as
 */
long identify_number(neighbor neighbor[K]) {
  long identified = -1;
  long max_freq = -1;
  long freqs[10][2] = {{0}};
  for (long i = 0; i < K; i += 1) {
    freqs[neighbor[i].neighbor][0] += 1;
    if (freqs[neighbor[i].neighbor][0] == 1) {
      freqs[neighbor[i].neighbor][1] = neighbor[i].distance;
    }
    if (freqs[neighbor[i].neighbor][0] > 1 && neighbor[i].distance < freqs[neighbor[i].neighbor][1]){
      freqs[neighbor[i].neighbor][1] = neighbor[i].distance;
    }
  }
  
  for (long j = 0; j < 10; j += 1) {
    if (freqs[j][0] > max_freq) {
      identified = j;
      max_freq = freqs[j][0];
    }
    if ((freqs[j][0] == max_freq) && (freqs[j][1] < freqs[identified][1] || (freqs[j][1] == freqs[identified][1] && j < identified))) {
        identified = j;
      }
    }
  return identified;
}


/**
 * The main function to test the samples and print both the actual number as well 
 * as the identified number. On top of that, this function also prints the accuracy
 * of the readings
 *
 * @param[in] train A pointer to the struct array that contains training samnples
 * @param[in] test A pointer to the struct array that contains testing samples
 * @param[in] n1 The size of training samples
 * @param[in] n2 The size of testing samples
 */
void test_sample(digit *train, digit *test, size_t n1, size_t n2) {
  neighbor neighbor[K];
  long counter = 0;
  for (size_t i = 0; i < n2; i += 1) {
    for (size_t j = 0; j < K; j += 1) {
      neighbor[j].neighbor = -1;
      neighbor[j].distance = -1;
    }

    for (size_t k = 0; k < n1; k += 1) {
      long distance = compute_distance(train[k].sample, test[i].sample, neighbor[K-1].distance);
      if (distance != -1) {
        insert(train[k].label, neighbor, distance);
      }
    }

    long number = test[i].label;
    long identified = identify_number(neighbor);
    if (number == identified) {
      counter += 1;
    }
    cs1010_print_long(number);
    cs1010_print_string(" ");
    cs1010_println_long(identified);
  }
  double accuracy = (double)counter/(double)n2 * 100;
  cs1010_println_double(accuracy);
}

/**
 * To free the structure memory 
 *
 * @param[in,out] input A pointer to the struct array
 * @param[in] size The number of structures to be freed
 *
 */
void free_mem(digit *input, size_t size) {
  for (size_t i = 0; i < size; i += 1) {
    for (size_t j = 0; j < NROWS; j += 1) {
      free(input[i].sample[j]);
    }
    free(input[i].sample);
  }
  free(input);
}


int main() {
  size_t n1 = cs1010_read_size_t(); 
  digit *train = calloc(n1, sizeof(digit));
  if (train == NULL) {
    return -1;
  }
  for (size_t i = 0; i < n1; i += 1) {
    train[i].label = cs1010_read_long();
    train[i].sample = read(NROWS);
    if (train[i].sample == NULL) {
      free_mem(train, i);
      return -1;
    }
  }

  
  size_t n2 = cs1010_read_size_t();
  digit *test = calloc(n2, sizeof(digit));
  if (test == NULL) {
    free_mem(train, n1);
    return -1;
  }
  for (size_t i = 0; i < n2; i += 1) {
    test[i].label = cs1010_read_long();
    test[i].sample = read(NROWS);
    if (test[i].sample == NULL) {
      free_mem(train, n1);
      free_mem(test, i);
      return -1;
    }
  }

  test_sample(train, test, n1, n2);

  free_mem(train, n1);
  free_mem(test, n2);
}
