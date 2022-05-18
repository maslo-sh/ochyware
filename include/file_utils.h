#ifndef FULE_UTILS
#define FILE_UTILS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "consts.h"
#include "log_types.h"

int read_file_to_buff(char *filename, char **buffer);

void remove_trailing_space(char buff[]);

#endif