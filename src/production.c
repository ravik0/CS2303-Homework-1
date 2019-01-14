/*
 * production.c
 *
 *  Created on: Nov 3, 2018
 *      Author: Therese Smith
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "production.h"
#include <math.h>

bool production(int argc, char* argv[])
{
	bool results = false;
	printf("CALENDAR\n");


	return results;
}

int calculate_days_in_month(int year, int month)
{
	int answer = -1;
	if(year < 1752) answer = -1;
	else if (month == 1 && is_leap_year(year) == 1) answer = 29;
	else if (month == 1) answer = 28;
	else if (month == 3 || month == 5 || month == 8 || month == 10) answer = 30;
	else if (is_valid_month(month) == 1) answer = 31;

	return(answer);
}
int is_leap_year(int year)
{
	int ans = year > 1751 ? year%4 == 0 && year%100 != 0 ? 1 : year%400 == 0 ? 1 : 0 : -1;

	return ans;

}
int calculate_day_of_week(int day, //first day of month is 1
		int month, //uses 0 for January
		int year)
{//invalid input gets a -1 answer
	int ans = -1;
	if(is_valid_month(month) == 1 && is_valid_day(year, month, day) == 1) {
		int m = month == 0 ? 11 : month == 1 ? 12 : month-1;
		int D = (month == 0 || month == 1) ? (year % 100 == 0 ? 99 : year%100-1) : year%100 ;
		int C = (month == 0 || month == 1) ? (year % 100 == 0 ? year/100-1 : year/100) : year/100;
		int f = day + floor((13*m-1)/5)+D+floor(D/4)+floor(C/4)-2*C;
		if(f < 0) {
			f = f%7+7;
		}
		else {
			f = f%7;
		}
		ans = f;
	}
	return ans;
}

int is_valid_month(int month) {
	return month >= 0 && month <= 11 ? 1 : -1;
}

int is_valid_day(int year, int month, int day) {
	if(month == 1 && is_leap_year(year) == 1) {
		return day >= 1 && day <= 29;
	}
	else if (month == 1) {
		return day >= 1 && day <= 28;
	}
	else if (month == 3 || month == 5 || month == 8 || month == 10) {
		return day >= 1 && day <= 30;
	}
	else {
		return day >= 1 && day <= 31;
	}
 }

