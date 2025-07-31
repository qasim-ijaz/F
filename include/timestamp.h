#ifndef TIME_STAMP
#define TIME_STAMP

#include <time.h>
#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "secure.h"

struct timedata {

       int year;
       int month;
       int dayofmonth;
       int hour;
       int min;
       int sec;
       int nsec;     
};

/* Parse timestam given by user and determine if it is valid */
struct timedata timestamp_parse(char *date);

/* Fill tspec with suitable data */
bool construct_timespec(struct timespec *tspec, struct stat *st, struct timedata *td, int mode);

/* Change timestamp of a file */
bool change_timestamp(char *filename, char *timestamp, int mode);

/* Check if year value provided by user is valid */
int year_check(int year);

/* Check if month value provided by user is valid */
int month_check(int month);

/* Check if day value provided by user is valid */
int day_check(int day);

/* Check if hour value provided by user is valid */
int hour_check(int time);

/* Check if min value provided by user is valid */
int min_sec_check(int time);

#endif
