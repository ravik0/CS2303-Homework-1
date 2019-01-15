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

bool production(int argc, char* argv[])
{
	bool results = false;
	int year = -1;
	if(argc == 2) {
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
			printf("     ");
		}
		for(int j = 1; j <= days; j++) {
			int day = calculate_day_of_week(j, i, year);
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
			if(j == days && day != 6) {
				printf("\n");
			}
		}
	}
	printf("\n");
	results = true;
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
	if(is_valid_month(month) == 1 && is_valid_day(year, month, day) == 1 && year >= 1752) { //if invalid input returns -1
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
		if(f == 7) f = 0;
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

