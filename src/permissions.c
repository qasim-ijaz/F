#include "../include/permissions.h"

bool perm_change_nonnumeric(char *filename, char *perm)
{ 
     if (strlen(perm) == 9) {  
         mode_t m = 0;

         (perm[0] == 'r') ? (m |= 0400) : 0;
         (perm[1] == 'w') ? (m |= 0200) : 0;
         (perm[2] == 's' || perm[2] == 'x') ? (m |= 0100)  : 0;  // Owner
         (perm[2] == 'S' || perm[2] == 's') ? (m |= 04000) : 0;
 
         (perm[3] == 'r') ? (m |= 0040) : 0;
         (perm[4] == 'w') ? (m |= 0020) : 0;
         (perm[5] == 's' || perm[5] == 'x') ? (m |= 0010)  : 0;  // Group
         (perm[5] == 'S' || perm[5] == 's') ? (m |= 02000) : 0;

         (perm[6] == 'r') ? (m |= 0004) : 0;
         (perm[7] == 'w') ? (m |= 0002) : 0;
         (perm[8] == 't' || perm[8] == 'x') ? (m |= 0001)  : 0;  // Other
         (perm[8] == 'T' || perm[8] == 't') ? (m |= 01000) : 0;
 
         if (chmod(filename, m) != 0) {
             perror("f: chmod() failed");
             return false;
         } 
         return true;
     }
    
     fprintf(stderr, "f: invalid permission '%s' provided\n", perm);
     return false;
}

bool perm_change_numeric(char *filename, char *perm)
{ 
     if (strlen(perm) > 4) {
         fprintf(stderr, "f: invalid permission '%s' provided\n", perm);
         return false;
     }

     for (char *ptr = perm; *ptr; ptr++) {
          if (!(*ptr >= '0' && *ptr <= '7')) {
              fprintf(stderr, "f: invalid permission '%s' provided\n", perm);
              return false;
          }
     }

     errno = 0; 
     mode_t m = strtol(perm, NULL, 8); 

     if (errno != 0) {
         fprintf(stderr, "f: strtol() failed\n");
         return false;
     }

     if (chmod(filename, m) != 0) {
         perror("f: chmod() failed");
         return false;
     }

     return true;
}
 
bool change_permission(char *filename, char *perm, int mode) {
     
     if (mode == 0)
         return perm_change_numeric(filename, perm);

     return perm_change_nonnumeric(filename, perm);
}
