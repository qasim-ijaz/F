#include "../include/secure.h"

void *safe_malloc(size_t size)
{
     void *ptr = malloc(size);

     if (ptr == NULL && (size > 0)) {
         perror("f: malloc() failed");         
         exit(EXIT_FAILURE);
     }

     return ptr;
}

bool fopen_check(FILE *fp)
{    
     return (fp == NULL) ? (false) : (true);   
}

void input_int_check(char *errmessage, char *input)
{
     for (char *ptr = input; *ptr; ptr++) { 
          if (!(*ptr >= '0' && *ptr <= '9')) {
              fprintf(stderr, "%s\n", errmessage);
              exit(EXIT_FAILURE);
          }
     }
}

void file_copy_cleanup(FILE *source, FILE *dest, char *path)
{
     (source != NULL)   ? (fclose(source))    : 0;
     (dest   != NULL)   ? (fclose(dest))      : 0;
     (path   != NULL)   ? (free(path))        : 0;
}
