/**
 * CS1010 Semester 1 AY22/23
 * Assignment 8: maze
 *
 * @file: maze.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define EMPTY '.'
#define WALL  '#'
#define USER  '@'

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

/**
 * To store and return the original maze inserted by user
 *
 * @param[in] nrows The number of rows
 * 
 * @return Returns the maze in to the array in the form of chars 
 */
char **read_maze(long nrows) {
  char **maze = calloc((size_t)nrows, sizeof(char *));
  if (maze == NULL) {
    return NULL;
  }

  for (long i = 0; i < nrows; i += 1) {
    maze[i] = cs1010_read_word();
    if (maze[i] == NULL) {
      for (long j = 0; j < i; j += 1){
        free(maze[j]);
      }
      return NULL;
    }
  }
  return maze;
}


/**
 * A 2D array that copies the original maze 
 *
 * @param[in,out] maze The original maze that is going to be copied
 * @param[in] nrows The number of rows
 * @param[in] ncols The number of columns
 *
 * @return The copied 2D array
 */
char **temp_maze(char **maze, long nrows, long ncols) {
  char **temp = calloc((size_t)nrows, sizeof(char *)) ;
  if (temp == NULL){
    return NULL;
  }

  for (long i = 0; i < nrows; i += 1) {
    temp[i] = calloc((size_t)ncols + 1, sizeof(char));
    if (temp[i] == NULL) {
      for (long j = 0; j < i; j += 1) {
        free(temp[j]);
      }
      return NULL;
    }
  }

  for (long i = 0; i < nrows; i += 1) {
    for (long j = 0; j < ncols + 1; j += 1) {
      temp[i][j] = maze[i][j];
    }
  }
  return temp;
}


/**
 * Print one row of the maze to the screen (with colors)
 * 
 * @param[in] maze_row The 1D array representing a row of maze.
 */
void print_maze_row_with_color(char *maze_row) {
  long l = (long)strlen(maze_row); 
  for (long j = 0; j < l; j++) {
    if (maze_row[j] == EMPTY) {
      cs1010_print_string(BLUE);
    } else if (maze_row[j] == USER) {
      cs1010_print_string(RED);
    } else {
      cs1010_print_string(YELLOW);
    }
    putchar(maze_row[j]);
  }
  cs1010_println_string("");
  cs1010_print_string(RESET);
}


/**
 * Print the maze to the screen.
 * 
 * @param[in] maze The 2D array representing the maze.
 * @param[in] nrows The number of rows
 * @param[in] steps The number of steps taken so far.
 */
void print_maze(char **maze, long nrows, long steps) {
  if (isatty(fileno(stdout))) {
    cs1010_clear_screen();
  }
  for (long i = 0; i < nrows; i += 1) {
    if (!isatty(fileno(stdout))) {
      cs1010_println_string(maze[i]);
    } else {
      print_maze_row_with_color(maze[i]);
    }
  }
  cs1010_println_long(steps);
  if (isatty(fileno(stdout))) {
    usleep(100*1000);
  }
}

/**
 * Find the current position of Scully in the maze
 *
 * @param[in] maze The layout of the maze
 * @param[in] nrows The number of rows
 * @param[in] ncols The number of columns
 * @param[out] scully_row The current position of Scully in terms of row
 * @param[out] scully_col The current position of Scully in terms of column
 */
void find_scully(char **maze, long nrows, long ncols, long *scully_row, long *scully_col) {
  for (long i = 0; i < nrows; i += 1) {
    for (long j = 0; j < ncols; j += 1) {
      if (maze[i][j] == USER) {
        *scully_row = i;
        *scully_col = j;
        return;                                                  
      }
    }
  }
}

/**
 * To move Scully from one cell to another inside the maze
 *
 * @param[in] maze The 2D array that stores the maze
 * @param[in,out] temp The maze that stores the path that Scully has taken
 * @param[in] prev_row Current position of Scully in terms of row
 * @param[in] prev_col Current position of Scully in terms of column
 * @param[in] curr_row The position Scully will be moving to in terms of row
 * @param[in] curr_col The position Scully will be moving to in terms of column
 * @param[in,out] counter The number of moves Scully has made
 * @param[in] nrows The number of rows
 */
void move(char **maze, char **temp, long prev_row, long prev_col, long curr_row, long curr_col, long *counter, long nrows) {
  *counter += 1;
  maze[prev_row][prev_col] = EMPTY;
  maze[curr_row][curr_col] = USER;
  //places a wall to block scully from going to the same path she has taken before
  temp[curr_row][curr_col] = WALL;   
  print_maze(maze, nrows, *counter);
}


/**
 * To check if adjacent cells are empty and if scully has walked this path before
 *
 * @param[in,out] maze The 2D array representing the maze
 * @param[in,out] temp The 2D array that stores the path Scully has taken before
 * @param[in] prev_row The row Scully was originally at
 * @param[in] prev_col The column Scully was originally at
 * @param[in] curr_row The current row of Scully
 * @param[in] curr_col The current colum of Scully
 * @param[in] nrows The number of rows
 * @param[in] ncols The number of columns
 * @param[in,out] counter Number of moves that Scully has taken
 *
 *@return Returns true if Scully reaches a border cell, otherwise false if
  she cannot find her way out
 */
bool next(char **maze, char **temp, long prev_row, long prev_col, long curr_row, long curr_col, long nrows, long ncols, long *counter) {
  if (curr_row == 0 || curr_row == nrows - 1 || curr_col == 0 || curr_col == ncols - 1) {
    return true; 
  }

  if ((maze[curr_row - 1][curr_col] == EMPTY) && (temp[curr_row - 1][curr_col] == EMPTY)) {
    move(maze, temp, curr_row, curr_col, curr_row - 1, curr_col, counter, nrows);
    if (next(maze, temp, curr_row, curr_col, curr_row - 1, curr_col, nrows, ncols, counter)) {
      return true;
    }
  }

  if ((maze[curr_row][curr_col + 1] == EMPTY) && (temp[curr_row][curr_col + 1] == EMPTY)) { 
    move(maze, temp, curr_row, curr_col, curr_row, curr_col + 1, counter, nrows);
    if (next(maze, temp, curr_row, curr_col, curr_row, curr_col + 1, nrows, ncols, counter)) {
      return true;
    }
  }

  if ((maze[curr_row + 1][curr_col] == EMPTY) && (temp[curr_row + 1][curr_col] == EMPTY)) { 
    move(maze, temp, curr_row, curr_col, curr_row + 1, curr_col, counter, nrows);
    if (next(maze, temp, curr_row, curr_col, curr_row + 1, curr_col, nrows, ncols, counter)) { 
      return true;
    }
  }

  if ((maze[curr_row][curr_col - 1] == EMPTY) && (temp[curr_row][curr_col - 1] == EMPTY)) { 
    move(maze, temp, curr_row, curr_col, curr_row, curr_col - 1, counter, nrows);
    if (next(maze, temp, curr_row, curr_col, curr_row, curr_col - 1, nrows, ncols, counter)) {
      return true;
    }
  }
  //For backtracking
  if (prev_col != -1) {
    move(maze, temp, curr_row, curr_col, prev_row, prev_col, counter, nrows);
  }
  return false;
}


/**
 * The function call to have scully get out of the maze
 *
 * @param[in,out] maze The 2D array that stores the layout of the maze
 * @param[in,out] temp The temporary 2D array that stores the path that Scully has taken
 * @param[in] nrows The number of rows
 * @param[in] ncols The number of columns
 * @param[out] counter The number of moves Scully has made
 */
void solve_maze(char **maze, char **temp, long nrows, long ncols, long *counter) {
  long scully_row;
  long scully_col;
  find_scully(maze, nrows, ncols, &scully_row, &scully_col);
  next(maze, temp, -1, -1, scully_row, scully_col, nrows, ncols, counter);
}


int main() {
  long nrows = cs1010_read_long();
  long ncols = cs1010_read_long();
  char **maze = read_maze(nrows);
  char **temp = temp_maze(maze, nrows, ncols);
  if (maze == NULL || temp == NULL){
    return 1;
  }
  long counter = 0;
  print_maze(maze, nrows, counter);
  solve_maze(maze, temp, nrows, ncols, &counter); 
  for (long i = 0; i < nrows; i += 1){
    free(maze[i]);
    free(temp[i]);
  }
  free(maze);
  free(temp);
  maze = NULL;
  temp = NULL;
}
