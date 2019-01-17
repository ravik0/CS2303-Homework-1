/*
 * production.c
 *
 *  Created on: Nov 3, 2018
 *      Author: Ravi Kirschner
 *      @author Ravi Kirschner
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "production.h"
#include <math.h>

/**
 Specify the year either as the first program argument, or pass in an argument at run-time and it
 will print a calendar from January to December.
 * @param argc Number of words on the command line
 * @param argv Array of pointers to character strings representing the words on the command line.
 * @return true if Program was able to print a calendar.
 *         false if User entered bad input.
 */
bool production(int argc, char* argv[])
{

	bool results = false;
	bool done = false;
	//get the year, Usage as needed.
	int year = -1;
	puts("CALENDAR");
	if(argc<2)
	{
		puts("Enter a year");
		scanf("%d",&year);
		if(year<1752)
		{
			printf("Usage: Year should be greater than 1751, received %d.\n",year);
			done = true;
		}
	}
	else
	{
		char* ptr=0;
		long year_l = strtol(argv[1],&ptr,10);
		year = (int)year_l;
		if(year<1752)
		{
			printf("Usage: Year should be greater than 1751, received %d.\n",year);
			done = true;
		}
	}
	if(!done) {
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
	}
	if(!done) {
		results = true; //if nothing failed, result is true.
	}
	return results;
}

/** Calculates how many days are in a given month for a given year.
 * @param year The year we are checking.
 * @param month The month we are checking. Range 0 through 11, where January = 0.
 * @return Days of the month in that specific year
 *         -1 if invalid input (e.g., year < 1752, month out of range).
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

/** Test if a given year is a leap year or not.
 * @param year The year we are testing
 * @return 1 if it is a valid leap year.
 *         0 if a valid year, but not a leap year.
 *        -1 if not a valid year (i.e. before the calendar rule changed in 1752).
 */
int is_leap_year(int year)
{
	int ans = year > 1751 ? (year%4 == 0 && year%100 != 0) ? 1 : (year%400 == 0) ? 1 : 0 : -1;
	return ans;

}

/** Determines what day of the week a particular date falls on.
 * @param day Day of the month, counting from 1.
 * @param month Range 0 through 11, where January = 0.
 * @param year The year.
 * @return -1 for invalid input (e.g., year < 1752, month out of range,
 *            day < 1 or > appropriate for that month & year
 *         0 through 6, where Sunday = 0.
 *
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

