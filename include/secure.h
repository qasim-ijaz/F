#ifndef SEC
#define SEC

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* Safety wrapper for malloc() */
void *safe_malloc(size_t size); 

/* Check if fopen() call succeeded */
bool fopen_check(FILE *fp);

/* Check if 'input' is a series of numbers */
void input_int_check(char *errmessage, char *input);

/* Clean up resources and exit gracefully in copy_file */
void file_copy_cleanup(FILE *source, FILE *dest, char *path);

#endif
