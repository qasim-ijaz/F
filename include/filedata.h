#ifndef FILE_DATA
#define FILE_DATA

#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "file.h"

/* Print all file data */
bool file_data(char *filename);

/* print file group ID*/
void file_data_gid(struct stat *st);

/* print file user ID*/
void file_data_uid(struct stat *st);

/* print file type*/
void file_data_type(struct stat *st);

/* print file inode number*/
void file_data_inode(struct stat *st);

/* print file access and modify times*/
void file_data_time(struct stat *st);

/* print size of file with suitable units*/
void file_data_size(struct stat *st);

/* print file mode and special permissions */
void file_data_mode(struct stat *st);

/* print file owner permissions */
void file_data_ownerp(struct stat *st);

/* print file group permissions */
void file_data_groupp(struct stat *st);

/* print file other permissions*/
void file_data_otherp(struct stat *st);

#endif
