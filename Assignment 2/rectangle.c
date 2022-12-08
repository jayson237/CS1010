/**
 * CS1010 Semester 1 AY22/23
 * Assignment 2: Rectangle
 *
 * @file: rectangle.c
 * @author: Jayson Ng (Group E03)
 */
#include "cs1010.h"

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_RIGHT "╝"
#define BOTTOM_LEFT "╚"
#define HORIZONTAL "═"
#define VERTICAL "║"

void draw_rectangle (long width, long height) {
  for (long y = 1; y <= height; y+=1) {
    for (long x = 1; x <= width; x+=1) {
      if (y == 1 && x == 1) {
        cs1010_print_string(TOP_LEFT);
      } else if (y == 1 && x == width) {
        cs1010_print_string(TOP_RIGHT);
      } else if (x == 1 && y == height) {
        cs1010_print_string(BOTTOM_LEFT);
      } else if (x == width && y == height) {
        cs1010_print_string(BOTTOM_RIGHT);
      } else if (x == 1 || x == width){
        cs1010_print_string(VERTICAL);
      } else if (y == 1 || y == height) {
        cs1010_print_string(HORIZONTAL);
      } else {
        cs1010_print_string(" ");
      }
    }
    cs1010_println_string("");
  }
}


int main() {
  long width = cs1010_read_long();
  long height = cs1010_read_long();
  draw_rectangle(width,height);
}

