#include "../include/file.h"

char *path_construct(char *filename, char *to)
{
    size_t len = strlen(to) + strlen(filename) + 2;

    char *path = safe_malloc(len);
    path[0] = '\0';

    strcat(path, to);
    strcat(path, "/");
    strcat(path, path_base(filename));

    return path;
}

char *path_base(char *filename)
{
     char *copy = filename;

     for (char *ptr = filename; *ptr; ptr++) {
         if (*ptr == '/')
                  copy = ptr+1;
     }
     
     return copy;
}

bool create_file(char *filename)
{ 
     FILE *fp = fopen(filename, "w");

     if (fopen_check(fp) == false) {
         perror("f: failed to create file");
         return false;
     }

     fclose(fp);
     return true;
}

bool delete_file(char *filename)
{    
     if (remove(filename) == -1) {
         perror("f: failed to delete file");
         return false;
     }
    
     return true;
}

bool copy_file(char *filename, char *to)
{ 
    FILE *source_file = fopen(filename, "rb");        

    if (fopen_check(source_file) == false) {
        fprintf(stderr, "f: source file '%s' is invalid: %s\n", filename, strerror(errno));
        return false;
    }

    char *path = path_construct(filename, to);
    FILE *dest_file = fopen(path, "wb"); 
   
    if (fopen_check(dest_file) == false) {
        fprintf(stderr, "f: destination '%s' is invalid: %s\n", to, strerror(errno));
        file_copy_cleanup(source_file, NULL, path);
        return false;
    }
 
    struct stat status;

    if (stat(filename, &status) != 0) {
        fprintf(stderr, "f: failed to stat '%s': %s\n", filename, strerror(errno));
        delete_file(path);
        file_copy_cleanup(source_file, dest_file, path);
        return false;
    }
 
    if (chmod(path, status.st_mode) != 0) {
        perror("f: chmod() failed\n");
        delete_file(path);
        file_copy_cleanup(source_file, dest_file, path);
        return false;
    }
  
    char buffer[READ_BUFSIZE];

    size_t r;    
    
    if (status.st_size > 0) { // if file not empty then copy contents
        while ((r = fread(buffer, 1, READ_BUFSIZE, source_file)) > 0) {
               if (fwrite(buffer, 1, r, dest_file) != r) {
                   fprintf(stderr, "f: write error occurred: %s", strerror(errno));
                   delete_file(path); 
                   file_copy_cleanup(source_file, dest_file, path);
                   return false;
               }
        }

        if (ferror(source_file)) {
            fprintf(stderr, "f: read error occurred");        
            delete_file(path);
            file_copy_cleanup(source_file, dest_file, path);
            return false; 
        }
    }

    struct timespec timespec[2];

    construct_timespec(timespec, &status, NULL, -1);

    if (utimensat(AT_FDCWD, path, timespec, 0) != 0) {
        perror("f: file timestamp preservation failed\n");
        delete_file(path);
        file_copy_cleanup(source_file, dest_file, path);
        return false;
    }
        
    file_copy_cleanup(source_file, dest_file, path);
    return true;
}

bool move_file(char *filename, char *to)
{
    char *path = path_construct(filename, to);

    if (rename(filename, path) == 0) {
        free(path);
        return true;
    }

    bool ok = copy_file(filename, to) && delete_file(filename);
    if (!ok)
        fprintf(stderr, "f: failed to move file '%s'\n", filename);

    free(path);
    return ok;
}

bool rename_file(char *filename, char *newname)
{
    if (rename(filename, newname) != 0) { 
        perror("f: file rename failed");
        return false;
    }

    return true; 
}
