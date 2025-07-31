#ifndef PERM_H
#define PERM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>

/* Change file permsission with numeric perm*/
bool perm_change_nonnumeric(char *filename, char *perm);

/* Change file permission with non-numeric perm*/
bool perm_change_numeric(char *filename, char *perm);

/* Change file permission */
bool change_permission(char *filename, char *perm, int mode);

#endif
