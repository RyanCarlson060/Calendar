#include "date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* validMonths[] = {"Jan", "Feb", "Mar", "Apr","May","Jun","Jul","Aug","Sep",
"Oct","Nov","Dec"};
int daysNormal[] = {31,28,31,30,31,30,31,31,30,31,30,31};
int daysLeap[] = {31,29,31,30,31,30,31,31,30,31,30,31};
int* daysInMonth[] = {daysNormal, daysLeap};

struct Date{

  char* month;
  int day;
  int year;

};

int getMonthNum(const char* month){
  int monthNum = -1;

  for (int i = 0; i < 12; i++) {
    if(strcmp(validMonths[i],month)==0){
      monthNum = i;
    }
  }

  return monthNum;
}

int isLeapYear(int year){
  int leapYear=0;
  if(year%4==0 && (year%100!=0 || year%400==0)){
    leapYear = 1;
  }
  return leapYear;
}

int isValidDate(const char* month, int day, int year){

  if(year<=0){
    return 0;
  }

  int leapYear = isLeapYear(year);

  int monthNum = getMonthNum(month);

  if(monthNum == -1){
    return 0;
  }

  if(day>daysInMonth[leapYear][monthNum] || day<=0){
    return 0;
  }

  return 1;

}


struct Date* createDate(const char* month, int day, int year){

  if(!isValidDate(month,day,year)){
    return NULL;
  }

  struct Date* date = malloc(sizeof(struct Date));
  date -> day = day;
  date -> year = year;
  date -> month = malloc((strlen(month)+1)*sizeof(char));
  strcpy(date->month, month);

  return date;

}


int destroyDate(struct Date* d){

  if(!d){
    return 0;
  }

  free(d->month);
  free(d);

  return 1;

}


char* getMonth(struct Date* date){
  if(!date){
    return 0;
  }

  char* copy = malloc((strlen(date->month)+1)*sizeof(char));
  strcpy(copy,date->month);

  return copy;

}

int getDay(struct Date* date){

  if(!date){
    return 0;
  }

  return date->day;

}


int getYear(struct Date* date){

  if(!date){
    return 0;
  }

  return date->year;

}

int setMonth(struct Date* date, const char* month){

  if(!date || !isValidDate(month,date->day,date->year)){
    return 0;
  }

  free(date->month);
  date -> month = malloc((strlen(month)+1)*sizeof(char));
  strcpy(date->month, month);

  return 1;

}


int setDay(struct Date* date, int day){

  if(!date || !isValidDate(date->month,day,date->year)){
    return 0;
  }

  date->day = day;

  return 1;
}


int setYear(struct Date* date, int year){

  if(!date || !isValidDate(date->month,date->day,year)){
    return 0;
  }

  date->year = year;

  return 1;
}


int compareDay(const struct Date* d1, const struct Date* d2){
  if(!d1 || !d2){
    return -2;
  }

  if(d1->year < d2->year){
    return -1;
  }else if(d1->year > d2->year){
    return 1;
  }

  if(getMonthNum(d1->month) < getMonthNum(d2->month)){
    return -1;
  }else if(getMonthNum(d1->month) > getMonthNum(d2->month)){
    return 1;
  }

  if(d1->day < d2->day){
    return -1;
  }else if(d1->day > d2->day){
    return 1;
  }

  return 0;

}


int nextDay(struct Date* date){

  if(!date){
    return 0;
  }

  int monthNum = getMonthNum(date->month);
  int leapYear = isLeapYear(date->year);
  int currentMonthDays = daysInMonth[leapYear][monthNum];

  if(date->day < currentMonthDays){
    setDay(date,date->day + 1);
    return 1;
  }

  if(monthNum<11){
    setDay(date,1);  
    setMonth(date,validMonths[monthNum+1]);
    return 1;
  }

  setDay(date,1);
  setMonth(date,validMonths[0]);
  setYear(date,date->year + 1);
  return 1;

}
