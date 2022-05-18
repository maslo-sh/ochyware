#ifndef ENCRYPTOR
#define ENCRYPTOR

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "log_types.h"


int encrypt_file(char *filename, int shift);

#endif