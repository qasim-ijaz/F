#include "../include/argparse.h"

bool print_help(void)
{     
     puts("Usage: f [OPTION] [ARGUMENTS]\n"
	  "or:    f [ARGUMENTS]\n"
	  "\n"
	  "-f <FILENAME>                                                       create a new empty file\n"
	  "-d <FILENAME>                                                       delete a file\n"
	  "-c <SOURCE> <DEST>                                                  make a copy of a file\n"
	  "-r <SOURCE> <NAME>                                                  rename a file\n"
	  "-m <SOURCE> <DEST>                                                  move a file\n"
	  "-i <FILENAME>                                                       display information about a file\n"
	  "\n"
	  "   --access <SOURCE> <YEAR MONTH DAYOFMONTH HOUR MIN SEC NSEC>      change file timestamp (access)\n"
	  "-t --modify <SOURCE> <YEAR MONTH DAYOFMONTH HOUR MIN SEC NSEC>      change file timestamp (modify)\n"
	  "   --all    <SOURCE> <YEAR MONTH DAYOFMONTH HOUR MIN SEC NSEC>      change file access and modify times\n"
	  "\n"
	  "-p --num  <SOURCE> <PERM>                                           change file perm numerically\n"
	  "   --alph <SOURCE> <PERM>                                           change file perm non-numerically\n"
	  "\n"
	  "-h                                                                  display this message\n"
	  "\n"
	  
	  "Examples:\n"
	  "\n"
	  "f -f newfile                            make new file called 'newfile'\n"
	  "f -d junkfile                           delete file called 'junkfile'\n"
	  "f -c /home/myfile /user/work            copy file 'myfile' to /user/work\n"
	  "f -r myfile yourfile                    rename file 'myfile' to 'yourfile'\n"
	  "f -m myfile /home/Documents/apps        move file 'myfile' to /home/Documents/apps\n"
	  "f -i myfile                             show information about file 'myfile'\n"
	  "f -t --access x 200012141310161234      change file access timestamp on 'x' to 2000/12/14 13:10:16.1234\n"
	  "f -t --modify x 200012141310161234      change file modify timestamp on 'x' to 2000/12/14 13:10:16.1234\n"
	  "f -t --all x 200012141310161234         change file access and modify timestamp on 'x' to 2000/12/14 13:10:16.1234\n"
	  "f -p --num myfile 644                   change permission on file 'myfile' to 644\n"
	  "f -p --alph myfile rw-r--r--            change permission on file 'myfile' to rw-r--r--\n"
	  "f -h                                    print help message");
}

bool bail(const char *fmt, const char *a, const char *b) {
    
     fprintf(stderr, fmt, a, b);
     fputs("Use 'f -h' for help.\n", stderr);
     return false;
}

#define MISSING(x, y)  bail("f: missing " x " after '%s'.\n", y, NULL)
#define INVALID(x, y)  bail("f: invalid data '%s' after '%s'.\n", x, y)

bool parse_args(int argc, char **argv) 
{ 
     if (argc == 1)
	 return bail("f: missing options.\n", NULL, NULL);

     if (strncmp(argv[1], "-t", 3) == 0) {
          if (argc == 2)
	      return MISSING("option", argv[1]);

          char *t_options[] = {"--access", "--modify", "--all"};
          
          for (int i = 0; i < 3; i++) {
               if (strncmp(argv[2], t_options[i], strlen(t_options[i])+1) == 0) { 
                   if (argc == 3)
		       return MISSING("filename", t_options[i]);
                   else if (argc == 4)
		       return MISSING("timestamp data", argv[3]);
                   else if (argc > 5)
		       return INVALID(argv[5], argv[4]);
                   return change_timestamp(argv[3], argv[4], i);
               }
          }
	
	  return false;
     }
     else if (strncmp(argv[1], "-p", 3) == 0) { 
          if (argc == 2)
	      return MISSING("option", argv[1]);

          char *p_options[] = {"--num", "--alph"}; 

          for (int i = 0; i < 2; i++) {
               if (strncmp(argv[2], p_options[i], strlen(p_options[i])+1) == 0) { 
                   if (argc == 3)
		       return MISSING("filename", p_options[i]);
                   else if (argc == 4)
		       return MISSING("permissions", argv[3]);
                   else if (argc > 5)
		       return INVALID(argv[5], argv[4]);
                   return change_permission(argv[3], argv[4], i);
               }    
          }

          return false;  
     }
     else if (strncmp(argv[1], "-f", 3) == 0) {
          if (argc == 2)
	      return MISSING("filename", argv[1]);
          else if (argc > 3)
	      return INVALID(argv[3], argv[2]);
          return create_file(argv[2]);        
     }
     else if (strncmp(argv[1], "-d", 3) == 0) {
          if (argc == 2)
	      return MISSING("filename", argv[1]);
          else if (argc > 3)
	      return INVALID(argv[3], argv[2]);
          return delete_file(argv[2]); 
     }
     else if (strncmp(argv[1], "-i", 3) == 0) {
          if (argc == 2)
	      return MISSING("filename", argv[1]);
          else if (argc > 3)
	      return INVALID(argv[3], argv[2]);  
          return file_data(argv[2]);    
     }
     else if (strncmp(argv[1], "-c", 3) == 0) {
          if (argc == 2)
	      return MISSING("filename", argv[1]);
          else if (argc == 3)
	      return MISSING("destination", argv[2]);
          else if (argc > 4)
	      return INVALID(argv[4], argv[3]);
          return copy_file(argv[2], argv[3]);
     }
     else if (strncmp(argv[1], "-m", 3) == 0) { 
          if (argc == 2)
	      return MISSING("filename", argv[1]);
          else if (argc == 3)
	      return MISSING("destination", argv[2]);
          else if (argc > 4)
	      return INVALID(argv[4], argv[3]);
          return move_file(argv[2], argv[3]);
     } 
     else if (strncmp(argv[1], "-r", 3) == 0) {
          if (argc == 2)
	      return MISSING("filename", argv[1]);
          else if (argc == 3)
	      return MISSING("name", argv[2]);
          else if (argc > 4)
	      return INVALID(argv[4], argv[3]);
          return rename_file(argv[2], argv[3]);
     }
     else if (strncmp(argv[1], "-h", 3) == 0) {
          if (argc > 2)
	      return INVALID(argv[2], argv[1]);
          return print_help();
     }
     
     fprintf(stderr, "f: invalid option '%s'.\nUse 'f -h' for help.\n", argv[1]);
     return false;
}              
