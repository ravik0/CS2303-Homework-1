/*
 * production.h
 *
 *  Created on: Nov 3, 2018
 *      Author: Ravi Kirschner
 */

#ifndef PRODUCTION_H_
#define PRODUCTION_H_
bool production(int argc, char* argv[]);
int calculate_days_in_month(int year, int month);
int is_leap_year(int year);
int calculate_day_of_week(int day, //first day of month is 1
		int month, //uses 0 for January
		int year);
int is_valid_month(int month);
int is_valid_day(int year, int month, int day);

#endif /* PRODUCTION_H_ */
