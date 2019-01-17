/*
 * production.c
 *
 *  Created on: Nov 3, 2018
 *      Author: Ravi Kirschner
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "production.h"
#include <math.h>

/**
 Function to create a calendar given a year.

 Specify the year either as the first program argument, or pass in an argument at run-time and it
 will print a calendar from January to December.
 @param argc the size of argv
 @param argv array of pointers to arguments in memory.
 @return true if succeeded, false if failed
 **/
bool production(int argc, char* argv[])
{
	bool results = false;
	int year = -1;
	if(argc >= 2) {
		year = strtol(argv[1], NULL, 10);
	}
	else {
		printf("Please enter a year: ");
		scanf("%d", &year);
	}
	if(year < 1752) {
		printf("The year was invalid!\n");
		results = false;
		return results;
	}
	printf("CALENDAR\n");
	for(int i = 0; i < 12; i++) {
		//switch case to figure out what month to print
		switch(i) {
			case 0:
				printf("January \n");
				break;
			case 1:
				printf("February \n");
				break;
			case 2:
				printf("March \n");
				break;
			case 3:
				printf("April \n");
				break;
			case 4:
				printf("May \n");
				break;
			case 5:
				printf("June \n");
				break;
			case 6:
				printf("July \n");
				break;
			case 7:
				printf("August \n");
				break;
			case 8:
				printf("September \n");
				break;
			case 9:
				printf("October \n");
				break;
			case 10:
				printf("November \n");
				break;
			case 11:
				printf("December \n");
				break;
			default:
				printf("Month Not Found");
				break;
		}
		printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat  \n");
		int days = calculate_days_in_month(year, i);
		for(int x = 0; x < calculate_day_of_week(1, i, year); x++) {
			printf("     "); //print the number of spaces required for the first day to land under the correct day of the week
		}
		for(int j = 1; j <= days; j++) {
			int day = calculate_day_of_week(j, i, year);
			//printing logic to make sure the number ends up in the correct spot
			if(day == 6) {
				if(j < 10) {
					printf("  %d  \n", j);
				}
				else {
					printf(" %d \n", j);
				}
			}
			else if(j < 10){
				printf("  %d  ", j);
			}
			else {
				printf(" %d  ", j);
			}
			//if end of the month and the day is not the final day of the week, end the line
			if(j == days && day != 6) {
				printf("\n");
			}
		}
	}
	printf("\n");
	results = true;
	return results;
}

/**
 Function to calculate the amount of days in a month.

 Given the year and a month, the function will calculate the number of days that month has.
 @param year the year that you want to look for the month in, must be greater than 1751
 @param month the month you want to find the number of days in
 @return -1 if the year is invalid, or the number of days in the month
 */
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

/**
 Function to determine if the year is a leap year

 If the year is valid, that is greater than 1751, the function will determine if the year is a leap year or not.
 @param year the year to look at
 @return -1 if the year is invalid, 0 if not leap year, and 1 if it is a leap year.
 */
int is_leap_year(int year)
{
	int ans = year > 1751 ? (year%4 == 0 && year%100 != 0) ? 1 : (year%400 == 0) ? 1 : 0 : -1;
	return ans;

}

/**
 Function to calculate the day of the week

 Given a valid month[0:11], year[1752:infinity), and day (must be valid within that year and month), it will produce the day
 of the week that that day falls on, where 0 is Sunday and 6 is Saturday.
 @param day the day
 @param month the month
 @param year the year
 @return -1 for invalid input, or the day of the week[0:6]
 */
int calculate_day_of_week(int day, //first day of month is 1
		int month, //uses 0 for January
		int year)
{//invalid input gets a -1 answer
	int ans = -1;
	if(is_valid_month(month) == 1 && is_valid_day(year, month, day) == 1 && year >= 1752) { //if invalid input returns -1
		int m = month == 0 ? 11 : month == 1 ? 12 : month-1; //shift month
		int D = (month == 0 || month == 1) ? (year % 100 == 0 ? 99 : year%100-1) : year%100;
		int C = (month == 0 || month == 1) ? (year % 100 == 0 ? year/100-1 : year/100) : year/100;
		int f = day + floor((13*m-1)/5)+D+floor(D/4)+floor(C/4)-2*C;
		if(f < 0) {
			f = f%7+7;
		}
		else {
			f = f%7;
		}
		if(f == 7) f = 0;
		ans = f;
	}
	return ans;
}

/**
 Function to tell whether a month is valid or not

 Given a month, it determines if it is between 0 and 11 inclusive.
 @param month the month
 @return -1 if not valid, 1 if valid.
 */
int is_valid_month(int month) {
	return month >= 0 && month <= 11 ? 1 : -1;
}

/**
 Function to tell whether a day is valid or not

 Given a month, day, and year, the function checks to see if it is possible for that day to occur
 in the year and month specified
 @param year the year
 @param month the month
 @param day the day
 @return -1 if invalid day, 1 if valid.
 */
int is_valid_day(int year, int month, int day) {
	if(month == 1 && is_leap_year(year) == 1) {
		return day >= 1 && day <= 29; //if leap year
	}
	else if (month == 1) {
		return day >= 1 && day <= 28; //if not leap year
	}
	else if (month == 3 || month == 5 || month == 8 || month == 10) {
		return day >= 1 && day <= 30;
	}
	else {
		return day >= 1 && day <= 31;
	}
 }

