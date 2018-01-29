#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#define INVALID_DATE (-1)
#endif /* __PROGTEST__ */

#define FIRST_FULL_MOON (2.49878487)
#define PERIOD (29.53059027)
#define STARTING_YEAR (1999)
#define MIN_YEAR (2000)

/*
Returns 1 if the year is leap, 0 if not.p
-------------------------------------------------
First parameter is a year.
*/
int isLeapYear(int y){
	if(y%4000 == 0)
		return 0;
	else if(y%400 == 0)
		return 1;
	else if(y%100 == 0)
		return 0;
	else if(y%4 == 0)
		return 1;
	else
		return 0;
}

/*
Returns the number of days in a month.
-------------------------------------------------
First parameter is the month.
Second parameter is if the year is leap or not.
						(1 = is leap, 0 = is not leap)
*/
int daysInMonth(int m, int isLeap){
	if(m == 2){
		if(isLeap)
			return 29;
		else
			return 28;
	}
	else if(m == 4 || m == 6 || m == 9 || m == 11)
		return 30;
	else
		return 31;
}

/*
Converts date (years, months, days) to just days.
(from 1.1. 1999)
-------------------------------------------------
First parameter is the year.
Second parameter is the month.
Third parameter is the day.
*/
int toDays(int y, int m, int d){
	int days = 0;
	
	for(int i = STARTING_YEAR; i<y; i++){
		if(isLeapYear(i))
			days += 366;
		else
			days += 365;
	}
	for(int i = 1; i<m; i++)
		days += daysInMonth(i, isLeapYear(y));
	days += d;
	return days;
}

/*
Converts days to date.
-------------------------------------------------
First parameter is the number of days.
Next three parameters are pointers to year, month,
day. These pointers are the out parameters.
*/
void fromDays(int days, int * y, int * m, int * d){
	int yy = STARTING_YEAR;
	int mm = 1;
	*y = STARTING_YEAR;
	*m = 1;
	*d = 1;
	
	while(1){
		if(isLeapYear(yy) && days-366 <= 0)
			break;
		else if(days-365 <= 0)
			break;
		else if(isLeapYear(yy)){
			days -= 366;
			*y = *y+1;
		}
		else{
			days -= 365;
			*y = *y+1;
		}
		yy++;
	}
	while(1){
		if(days-daysInMonth(mm, isLeapYear(yy)) <= 0)
			break;
		days -= daysInMonth(mm, isLeapYear(yy));
		mm++;
		*m = *m+1;
	}
	*d = days;
}

/*
Returns 1 if there is a full moon on entered date,
otherwise returns 0.
If the date is invalid, it returns -1(INVALID_DATE)
-------------------------------------------------
First parameter is the year.
Second parameter is the month.
Third parameter is the day.
*/
int isFullMoon(int y, int m, int d){
	int maxDays = daysInMonth(m, isLeapYear(y));
	int days = toDays(y, m, d);
	double tmp = FIRST_FULL_MOON;
	
	if(y < MIN_YEAR || m > 12 || m < 1 || d < 1 || d > maxDays)
		return INVALID_DATE;

	while(days >= (int)tmp)
		tmp += PERIOD;
	return (int)(tmp-PERIOD) == days;
}

/*
If the date is invalid, it returns -1(INVALID_DATE),
otherwise returns 1.
Sets the year, month and day to the date
of the previous full moon. (to the variables
y, m, d)
-------------------------------------------------
First parameter is the year.
Second parameter is the month.
Third parameter is the day.
Next three parameters are pointers to the
year, month and day variables for the previous
full moon. 
These pointers are the out parameters.
*/
int prevFullMoon( int y, int m, int d, int * prevY, int * prevM, int * prevD ){
	int maxDays = daysInMonth(m, isLeapYear(y));
	int days = toDays(y, m, d);
	double tmp = FIRST_FULL_MOON;
	
	if(y < MIN_YEAR || m > 12 || m < 1 || d < 1 || d > maxDays)
		return INVALID_DATE;
		
	while(days >= (int)tmp)
		tmp += PERIOD;
	if((int)(tmp-PERIOD) == days)
		fromDays((int)(tmp-2*PERIOD), prevY, prevM, prevD);
	else
		fromDays((int)(tmp-PERIOD), prevY, prevM, prevD);
	return 1;
}

/*
If the date is invalid, it returns -1(INVALID_DATE),
otherwise returns 1.
Sets the year, month and day to the date
of the next full moon. (to the variables
y, m, d)
-------------------------------------------------
First parameter is the year.
Second parameter is the month.
Third parameter is the day.
Next three parameters are pointers to the
year, month and day variables for the next
full moon. 
These pointers are the out parameters.
*/
int nextFullMoon( int y, int m, int d, int * prevY, int * prevM, int * prevD ){
	int maxDays = daysInMonth(m, isLeapYear(y));
	int days = toDays(y, m, d);
	double tmp = FIRST_FULL_MOON;
	
	if(y < MIN_YEAR || m > 12 || m < 1 || d < 1 || d > maxDays)
		return INVALID_DATE;
		
	while(days >= (int)tmp)
		tmp += PERIOD;
		
	fromDays((int)(tmp), prevY, prevM, prevD);
	return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  int y, m, d;
  assert ( isFullMoon ( 2000, 7, 16 ) == 1 );
  assert ( isFullMoon ( 2017, 1, 11 ) == 0 );
  assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 1, 13 ) == 0 );
  assert ( isFullMoon ( 2017, 11, 3 ) == 0 );
  assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
  assert ( isFullMoon ( 2017, 11, 5 ) == 0 );
  assert ( isFullMoon ( 2019, 12, 11 ) == 1 );
  assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
  assert ( isFullMoon ( 2019, 12, 13 ) == 0 );
  assert ( prevFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
  assert ( prevFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2016 && m == 12 && d == 14 );
  assert ( prevFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
  assert ( prevFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
  assert ( prevFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 10 && d == 5 );
  assert ( prevFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
  assert ( prevFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2019 && m == 11 && d == 12 );
  assert ( prevFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
  assert ( prevFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2019 && m == 12 && d == 11 );
  assert ( nextFullMoon ( 2017, 1, 11, &y, &m, &d ) == 1 && y == 2017 && m == 1 && d == 12 );
  assert ( nextFullMoon ( 2017, 1, 12, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
  assert ( nextFullMoon ( 2017, 1, 13, &y, &m, &d ) == 1 && y == 2017 && m == 2 && d == 11 );
  assert ( nextFullMoon ( 2017, 11, 3, &y, &m, &d ) == 1 && y == 2017 && m == 11 && d == 4 );
  assert ( nextFullMoon ( 2017, 11, 4, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
  assert ( nextFullMoon ( 2017, 11, 5, &y, &m, &d ) == 1 && y == 2017 && m == 12 && d == 3 );
  assert ( nextFullMoon ( 2019, 12, 11, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( nextFullMoon ( 2019, 12, 12, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( nextFullMoon ( 2019, 12, 13, &y, &m, &d ) == 1 && y == 2020 && m == 1 && d == 10 );
  assert ( isFullMoon ( 2017, 1, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 2, 11 ) == 1 );
  assert ( isFullMoon ( 2017, 3, 12 ) == 1 );
  assert ( isFullMoon ( 2017, 4, 11 ) == 1 );
  assert ( isFullMoon ( 2017, 5, 10 ) == 1 );
  assert ( isFullMoon ( 2017, 6, 9 ) == 1 );
  assert ( isFullMoon ( 2017, 7, 9 ) == 1 );
  assert ( isFullMoon ( 2017, 8, 7 ) == 1 );
  assert ( isFullMoon ( 2017, 9, 6 ) == 1 );
  assert ( isFullMoon ( 2017, 10, 5 ) == 1 );
  assert ( isFullMoon ( 2017, 11, 4 ) == 1 );
  assert ( isFullMoon ( 2017, 12, 3 ) == 1 );
  assert ( isFullMoon ( 2018, 1, 2 ) == 1 );
  assert ( isFullMoon ( 2018, 1, 31 ) == 1 );
  assert ( isFullMoon ( 2018, 3, 2 ) == 1 );
  assert ( isFullMoon ( 2018, 3, 31 ) == 1 );
  assert ( isFullMoon ( 2018, 4, 30 ) == 1 );
  assert ( isFullMoon ( 2018, 5, 29 ) == 1 );
  assert ( isFullMoon ( 2018, 6, 28 ) == 1 );
  assert ( isFullMoon ( 2018, 7, 27 ) == 1 );
  assert ( isFullMoon ( 2018, 8, 26 ) == 1 );
  assert ( isFullMoon ( 2018, 9, 25 ) == 0 );
  assert ( isFullMoon ( 2018, 10, 24 ) == 1 );
  assert ( isFullMoon ( 2018, 11, 23 ) == 1 );
  assert ( isFullMoon ( 2018, 12, 22 ) == 1 );
  assert ( isFullMoon ( 2019, 1, 21 ) == 1 );
  assert ( isFullMoon ( 2019, 2, 19 ) == 1 );
  assert ( isFullMoon ( 2019, 3, 21 ) == 1 );
  assert ( isFullMoon ( 2019, 4, 19 ) == 1 );
  assert ( isFullMoon ( 2019, 5, 18 ) == 0 );
  assert ( isFullMoon ( 2019, 6, 17 ) == 1 );
  assert ( isFullMoon ( 2019, 7, 16 ) == 0 );
  assert ( isFullMoon ( 2019, 8, 15 ) == 1 );
  assert ( isFullMoon ( 2019, 9, 14 ) == 1 );
  assert ( isFullMoon ( 2019, 10, 13 ) == 1 );
  assert ( isFullMoon ( 2019, 11, 12 ) == 1 );
  assert ( isFullMoon ( 2019, 12, 12 ) == 0 );
  assert ( isFullMoon ( 2000, 14, 10 ) == INVALID_DATE );
  assert ( prevFullMoon ( 2000, 11, 31, &y, &m, &d ) == INVALID_DATE );
  assert ( nextFullMoon ( 2001, 2, 29, &y, &m, &d ) == INVALID_DATE );
  assert ( isFullMoon ( 2004, 2, 29 ) == 0 );
  assert ( prevFullMoon ( 2100, 2, 29, &y, &m, &d ) == INVALID_DATE );
  assert ( nextFullMoon ( 2000, 2, 29, &y, &m, &d ) == 1 && y == 2000 && m == 3 && d == 20 );
  return 0;
}
#endif /* __PROGTEST__ */
