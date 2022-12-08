/**
 * CS1010 Semester 1 AY22/23
 * Assignment 1: Taxi
 *
 * Read in four positive integer corresponding to the day of the week,
 * the hour and minute of boarding, and the distance travelled.  Print
 * to the standard output, the taxi fare for the trip.
 *
 * @file: taxi.c
 * @author: Jayson Ng (Group E03)
 */

#include "cs1010.h"
#include <stdbool.h>

bool is_weekday(long day){
  if (day<=5 && day>=1){
    return true;
  } return false;
}

bool is_morning_peak(long hour, long minute){
  if (((hour<9 && hour>=6)&&(minute<=59 && minute>=0)) || (hour==9 && minute<=29)) {
     return true;
   } return false; 
 }


bool is_evening_peak(long hour, long minute){ 
  if ((hour<=23 && hour>=18)&&(minute<=59 && minute>=0)){
    return true;
  } return false;
}

bool is_midnight_peak(long hour, long minute){
   if ((hour<=5 && hour>=0)&&(minute<=59 && minute>=0)){
     return true;
  } return false;
}

double metered(long distance){
  long distance1 = ((distance-1000)/400)+1;
  long distance2 = ((distance-10000)/350)+1;
  double answer;
  if (distance<=1000){
    answer = 3.9;
  } else if (distance<=10000 && ((distance-1000)%400!=0)){
    answer = 3.9 + ((double)distance1 * 0.24);
  } else if (distance<=10000 && ((distance-1000)%400==0)){
    answer = 3.9 + ((double)(distance-1000)/400)*0.24;
  } else if (distance>10000 && ((distance-10000)%350==0)){
    answer = 3.9 + (23*0.24)+((double)(distance-10000)/350*0.24);
  } else{
    answer = 3.9 + (23*0.24)+((double)distance2*0.24);
  } return answer;
}

double surcharge (long day, long hour, long minute, long distance){
  bool weekday = is_weekday(day);
  bool morning = is_morning_peak(hour, minute); 
  bool evening = is_evening_peak(hour, minute);
  bool midnight = is_midnight_peak(hour, minute);
  double before_surcharge = metered(distance);
  double answer;
  if ((weekday == true && morning == true)||(evening == true)){
    answer = 1.25 * before_surcharge;
  } else if (midnight == true){
    answer =  1.5 * before_surcharge;
  } else {
    answer = before_surcharge;
  } return answer;
}
  

int main()
{
 long day = cs1010_read_long();
 long hour = cs1010_read_long();
 long minute = cs1010_read_long();
 long distance = cs1010_read_long();
 cs1010_println_double(surcharge(day,hour,minute,distance));
}
