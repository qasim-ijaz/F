#ifndef FILE_H
#define FILE_H

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <utime.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>

#include "secure.h"
#include "timestamp.h"

#define READ_BUFSIZE 4096

/* Create a new file */
bool create_file(char *filename);

/* Delete a file */
bool delete_file(char *filename);

/* Copy a file */
bool copy_file(char *filename, char *to);

/* Move a file */
bool move_file(char *filename, char *to);  

/* Rename a file */
bool rename_file(char *filename, char *newname);

/* Appends 'filename' to the end of 'to' */
char *path_construct(char *filename, char *to);

/* Returns the file at the end of a path */ 
char *path_base(char *filename);

#endif
