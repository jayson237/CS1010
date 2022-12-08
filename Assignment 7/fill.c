/**
 * CS1010 Semester 1 AY22/23
 * Assignment 8: Fill
 *
 * @file: fill.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"
#include <stdbool.h>

/**
 * To create a 3D array
 *
 * @param[in] m The number of rows
 * @param[in] n The number of columns
 *
 * @return The 3D array that stores the input
 */
long ***read_pixels(size_t m, size_t n) {
  long ***pixels = calloc(m, sizeof (long **));
  if (pixels == NULL) {
    cs1010_println_string("Error");
    return NULL;
  }

  for (size_t i = 0; i < m; i += 1) {
    pixels[i] = calloc(n, sizeof (long *));
    if (pixels[i] == NULL) {
      cs1010_println_string("Error");
      for (size_t j = 0; j < i; j += 1) {
        free(pixels[j]);
      }
      free(pixels);
      return NULL;
    }

    for (size_t x = 0; x < n; x += 1) {
      pixels[i][x] = cs1010_read_long_array(3);
      if (pixels[i][x] == NULL) {
        cs1010_println_string("Error");
        return NULL;
      }
    }
  }
  return pixels;
}


/**
 * To paint a particular coordinate with certain RGB code
 *
 * @param[out] x The coordinate to be painted in terms of (x,y)
 * @param[out] y The coordinate to be pointed in terms of (x,y)
 * @param[out] pixels To-be-updated pixels
 * @param[in] color The color to-be-painted
 */
void paint(long x, long y, long ***pixels, long *color) {
  for (long i = 0; i < 3; i += 1) {
    pixels[x][y][i] = color[i];
  }
}


/**
 * To check whether a coordinate is the same segment to its adjacents
 *   
 * @param[in] x The coordinate to be painted in terms of (x,y)
 * @param[in] y The coordinate to be painted in terms of (x,y)
 * @param[in] m The number of rows
 * @param[in] n The number of columns
 * @param[in] pixels The 3D array that stores the RGBs
 * @param[in] curr_color The current color in the (x,y) coordinate
 *          
 * @return Returns true if two coordinates are in the same segment, otherwise false.
 */
bool is_same_segment(long x, long y, size_t m, size_t n, long ***pixels, long *curr_color) {
  if (x >= (long)m || x < 0 || y < 0 || y >= (long)n) {
    return false;
  }

  for (long i = 0; i < 3; i += 1) {
    if (pixels[x][y][i] != curr_color[i]) {
      return false;
    }
  }
  return true;
}


/**
 * To main recursion function to check the adjacents of (x,y) whether they are in the same segment, if yes, 
 * the same color will be filled with the same color too.
 *
 * @param[in,out] x The coordinate to be painted in terms of (x,y)
 * @param[in,out] y The coordinate to be painted in terms of (x,y)
 * @param[in] m The number of rows
 * @param[in] n The number of columns
 * @param[in] pixels The 3D array that stores the pixels' RGB codes
 * @param[in] curr_color The current color in the (x,y) coordinate
 * @param[in] color The color to-be-painted
 */
void fill_segment(long x, long y, size_t m, size_t n, long ***pixels, long *curr_color, long *color) {
     
  paint(x, y, pixels, color);
    
  if (is_same_segment(x + 1, y, m, n, pixels, curr_color)) {
    fill_segment(x + 1, y, m, n, pixels, curr_color, color);
  }

  if (is_same_segment(x - 1, y, m, n, pixels, curr_color)) {
    fill_segment(x - 1, y, m, n, pixels, curr_color, color);
  }

  if (is_same_segment(x, y + 1, m, n, pixels, curr_color)) {
    fill_segment(x, y + 1, m, n, pixels, curr_color, color);
  }

  if (is_same_segment(x, y - 1, m, n, pixels, curr_color)) {
    fill_segment(x, y - 1, m, n, pixels, curr_color, color);
  }
}


/**
 * To fill the coordinate and RGB according to the fill operation inputs
 *
 * @param[in] pixels The 3D array that stores the pixels' RGB codes
 * @param[in] m The number of rows
 * @param[in] n The number of columns
 */
void fill(long ***pixels, size_t m, size_t n) {
  long x = cs1010_read_long();
  long y = cs1010_read_long();
  long curr_color[3];

  for (long i = 0; i < 3; i += 1) {
    curr_color[i] = pixels[x][y][i];
  }

  long *color = cs1010_read_long_array(3);
  if (color == NULL) {
    cs1010_println_string("Error");
    return;
  }
  for (long i = 0; i < 3; i += 1) {
    if (curr_color[i] != color[i]) {
      fill_segment(x, y, m, n, pixels, curr_color, color);
    }
  }
  free(color);
  color = NULL;
}


/**
 * To print line on every one RGB code printed
 *
 * @param[out] pixels The 3D array that stores the RGB codes
 * @param[in,out] i The index of pixels in 1D
 * @param[in,out] j The index of pixels in 2D
 */
void print_line(long ***pixels, size_t i, size_t j) {
  //x = The index for each pixel
  for (size_t x = 0; x < 3; x += 1){
    if (x == 2) {
      cs1010_println_long(pixels[i][j][x]);
    } else {
      cs1010_print_long(pixels[i][j][x]);
      cs1010_print_string(" ");
    }
  }
} 


/**
 * To print every number of the RGB code of a pixel
 *
 * @param[out] pixels The 3D array that stores the RGB codes
 * @param[out] m The number of rows
 * @param[out] n The number of columns
 */
void print(long ***pixels, size_t m, size_t n) {
  cs1010_print_string("P3 ");
  cs1010_print_long((long)n);
  cs1010_print_string(" ");
  cs1010_print_long((long)m);
  cs1010_print_string(" ");
  cs1010_println_long(255);

  for (size_t i = 0; i < m; i += 1) {
    for (size_t j = 0; j < n; j += 1) {
      print_line(pixels, i , j);
    }
  }
}



int main() {
  size_t row = cs1010_read_size_t();
  size_t column = cs1010_read_size_t();
  long ***pixels = read_pixels(row,column); 
  if (pixels == NULL) {
    cs1010_println_string("Error");
    return 1;
  }

  size_t operations = cs1010_read_size_t();
  for (size_t i = 0; i < operations; i += 1) {
    fill(pixels, row, column);
  }

  print(pixels, row, column);

  for (size_t i = 0; i < row; i += 1) {
    for (size_t j = 0; j < column; j += 1) {
      free(pixels[i][j]);
    }
    free(pixels[i]);
  }
  free(pixels);
  pixels = NULL;
}  





































