#include "../include/timestamp.h"

struct timedata timestamp_parse(char *date) {

     int year = 0, month = 0, dayofmonth = 0, hour = 0, min = 0, sec = 0, nsec = 0;
     int date_size = strlen(date);

     if (date_size < 15 || date_size > 23) { 
         fprintf(stderr, "f: date '%s' is invalid\n", date);
         exit(EXIT_FAILURE);
     }

     input_int_check("f: date must not contain letters\n", date);
     sscanf(date, "%4d%2d%2d%2d%2d%2d%9d", &year, &month, &dayofmonth, &hour, &min, &sec, &nsec);

     if (year_check(year) && month_check(month) && day_check(dayofmonth) &&
         hour_check(hour) && min_sec_check(min) && min_sec_check(sec)) {

         struct timedata data = {year, month, dayofmonth, hour, min, sec, nsec};
         return data;
     }
     else {
         fprintf(stderr, "f: date '%s' does not exist\n", date);
         exit(EXIT_FAILURE);
     }
}

bool construct_timespec(struct timespec *tspec, struct stat *st, struct timedata *td, int mode) {

       if (st != NULL && td == NULL) {
           tspec[0].tv_sec = st->st_atim.tv_sec;
           tspec[0].tv_nsec = st->st_atim.tv_nsec;
           tspec[1].tv_sec = st->st_mtim.tv_sec;
           tspec[1].tv_nsec = st->st_mtim.tv_nsec;
       }
       else if (st == NULL && td != NULL) {
                struct tm tm;               

                tm.tm_sec   = td->sec;
                tm.tm_min   = td->min;
                tm.tm_hour  = td->hour;
                tm.tm_mon   = td->month - 1;
                tm.tm_year  = td->year - 1900;
                tm.tm_isdst = -1;
                tm.tm_mday  = td->dayofmonth;

                time_t epoch_seconds = mktime(&tm);

                if (mode == 0) {
                    tspec[0].tv_sec  = epoch_seconds;       // change access time
                    tspec[0].tv_nsec = td->nsec;
                    tspec[1].tv_nsec = UTIME_OMIT;
                }
                else if (mode == 1) {
                    tspec[0].tv_nsec = UTIME_OMIT;
                    tspec[1].tv_sec = epoch_seconds;     // change modify time
                    tspec[1].tv_nsec = td->nsec;
                }
                else {
                    tspec[0].tv_sec  = epoch_seconds;
                    tspec[0].tv_nsec = td->nsec;         // change access and modify time
                    tspec[1].tv_sec = epoch_seconds;
                    tspec[1].tv_nsec = td->nsec;
                } 
       }
       else {
            return false;
       }

       return true;
}

bool change_timestamp(char *filename, char *timestamp, int mode) {

     struct timedata data = timestamp_parse(timestamp); // parse timestamp into struct  
     struct timespec timespec[2];

     if (construct_timespec(timespec, NULL, &data, mode) != true) {
         fprintf(stderr, "f: failed to retrieve time data\n");
         return false;
     }

     if (utimensat(AT_FDCWD, filename, timespec, 0) != 0) {
         perror("f: timestamp change failed");
         return false;
     }

     return true;
}

int year_check(int year)
{
    return (year > 1900) ? 1 : 0;
}

int month_check(int month)
{
    return (month > 0 && month <= 12) ? 1 : 0;
}

int day_check(int day)
{
    return (day > 0 && day <= 31) ? 1 : 0;
}

int hour_check(int time)
{
    return (time >= 0 && time <= 23) ? 1 : 0;
}

int min_sec_check(int time)
{
    return (time >= 0 && time <= 59) ? 1 : 0;
}

