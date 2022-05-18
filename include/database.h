#ifndef HASH_DATABASE
#define HASH_DATABASE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consts.h"
#include "log_types.h"

extern char **HASH_DB;
extern int NUMBER_OF_HASHES; 
extern int DETECTED_VIRUSES;
extern int SCANNED_FILES;

int read_hash_database(char *filename);
int deallocate_db_memory();

#endif