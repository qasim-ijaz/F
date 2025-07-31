#ifndef ARG_P
#define ARG_P

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file.h"
#include "filedata.h"
#include "permissions.h"
#include "secure.h"
#include "timestamp.h"

/* Print a help message */
bool print_help(void);

/* Parse arguments given by user */
bool parse_args(int argc, char **argv);

#endif
