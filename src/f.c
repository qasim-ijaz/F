#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/argparse.h"

int main(int argc, char *argv[])
{
   bool main_exit = parse_args(argc, argv);
       
   (main_exit == false) ? exit(EXIT_FAILURE) : exit(EXIT_SUCCESS);
}
