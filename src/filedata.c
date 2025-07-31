#include "../include/filedata.h"

void file_data_gid(struct stat *st)
{
     struct group *grp;

     if ((grp = getgrgid(st->st_gid)) != NULL) {
         printf("[GID]: %lu (%s)\n", (unsigned long int) st->st_gid, grp->gr_name);
     }
     else {
         printf("[GID]: %lu\n", (unsigned long int) st->st_gid);
     }
}

void file_data_uid(struct stat *st)
{
     struct passwd *pwd;
   
     if ((pwd = getpwuid(st->st_uid)) != NULL) {
         printf("[UID]: %lu (%s)\n", (unsigned long int) st->st_uid, pwd->pw_name);
     }
     else {
         printf("[UID]: %lu\n", (unsigned long int) st->st_uid);
     }
}

void file_data_type(struct stat *st)
{
     switch (st->st_mode & S_IFMT) {

             case S_IFREG:  printf("[Type]: regular file\n");                                                break;
             case S_IFDIR:  printf("[Type]: directory\n");                                                   break;
             case S_IFLNK:  printf("[Type]: symbolic link\n");                                               break;
             case S_IFBLK:  printf("[Type]: block device\n");     printf("[Device ID]: %ld\n", st->st_rdev); break;
             case S_IFCHR:  printf("[Type]: character device\n"); printf("[Device ID]: %ld\n", st->st_rdev); break;
             case S_IFIFO:  printf("[Type]: FIFO/pipe\n");                                                   break;
             case S_IFSOCK: printf("[Type]: socket\n");                                                      break;
             default:       printf("[Type]: unknown type\n");                                                break;
     }
}

void file_data_inode(struct stat *st)
{
     printf("[Inode Numer]: %ld\n", st->st_ino);
}

void file_data_time(struct stat *st)
{
     char *mod_time = ctime(&st->st_mtime);
     char *access_time = ctime(&st->st_atime);

     if (mod_time != NULL)
         printf("[Last Modification]: %s", mod_time);

     if (access_time != NULL)
         printf("[Last Access]:       %s", access_time);
}

void file_data_size(struct stat *st)
{
     const char *units[9] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};

     double bytes = st->st_size;
     int i = 0;

     while (bytes > 1024) {

           i++;
           bytes /= 1024;
     }
      
     printf("[File Size]: %lf %s \n", bytes, units[i]);     
}

void file_data_mode(struct stat *st)
{
     int newline = 0;

     printf("[File Mode]: %04o\n", (unsigned) (st->st_mode & 07777u)); 
     printf("[Special Perms]:");

     if (st->st_mode & S_ISUID) {
         (st->st_mode & S_IXUSR) ? printf(" -SUID & EXE (s)- ") : printf(" -SUID Enabled (S)- ");
         newline = 1;
     }

     if (st->st_mode & S_ISGID) {
         (st->st_mode & S_IXGRP) ? printf(" -GUID & EXE (s)- ") : printf(" -GUID Enabled (S)- ");
         newline = 1;
     }

     if (st->st_mode & S_ISVTX) {
         (st->st_mode & S_IXOTH) ? printf(" -Sticky Bit & EXE (t)- ") : printf(" -Sticky Bit Enabled (T)- ");
         newline = 1;
     }

     (newline == 0) ? printf(" None\n") : printf("\n");
}

void file_data_ownerp(struct stat *st)
{
     printf("[Owner Perms]: ");

     (st->st_mode & S_IRUSR) ? printf("read ") : printf("(no read) ");
     (st->st_mode & S_IWUSR) ? printf("write ") : printf("(no write) ");
     (st->st_mode & S_IXUSR) ? printf("execute\n") : printf("(no execute)\n");   
}

void file_data_groupp(struct stat *st)
{
     printf("[Group Perms]: ");

     (st->st_mode & S_IRGRP) ? printf("read ") : printf("(no read) ");
     (st->st_mode & S_IWGRP) ? printf("write ") : printf("(no write) ");
     (st->st_mode & S_IXGRP) ? printf("execute\n") : printf("(no execute)\n");
}

void file_data_otherp(struct stat *st)
{ 
     printf("[Other Perms]: ");

     (st->st_mode & S_IROTH) ? printf("read ") : printf("(no read) ");
     (st->st_mode & S_IWOTH) ? printf("write ") : printf("(no write) ");
     (st->st_mode & S_IXOTH) ? printf("execute\n") : printf("(no execute)\n");
}

bool file_data(char *filename)
{
     struct stat st;

     if (stat(filename, &st) != 0) {
         perror("f: stat()");
         return false;
     }

     printf("[File]: %s\n", path_base(filename));

     file_data_type(&st);
     file_data_size(&st);

     file_data_uid(&st);
     file_data_gid(&st);

     file_data_inode(&st);
     file_data_time(&st);      

     file_data_mode(&st);
     file_data_ownerp(&st);   

     file_data_groupp(&st);   
     file_data_otherp(&st);
 
     return true;   
}
