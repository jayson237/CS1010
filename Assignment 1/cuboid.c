/**
 * CS1010 Semester 1 AY22/23
 * Assignment 1: Cuboid
 *
 * Read in three positive integer corresponding to the width,
 * length, and height of a cuboid from the standard input, and
 * print the total surface area and the length of its diagonal
 * to the standard output.
 *
 * @file: cuboid.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"
#include <math.h>

//computation function for the area of a rectangle
long area_of_rectangle(long width, long length){
  return (width*length); 
}

long surface_area(long width, long length, long height){
  return (2*area_of_rectangle(width,length))+(2*area_of_rectangle(length,height))+(2*area_of_rectangle(width,height));
}



double hypotenuse_of(double leg1, double leg2){
  return sqrt((leg1*leg1)+(leg2*leg2));
}


int main() 
  
{
 long width = cs1010_read_long();
 long length = cs1010_read_long();
 long height = cs1010_read_long();
 double diagonal = hypotenuse_of((double) width,(double) length);
 cs1010_println_long(surface_area(width,length,height));
 cs1010_println_double(hypotenuse_of(diagonal,(double)height));
}
