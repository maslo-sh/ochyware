#ifndef COMPARATOR
#define COMPARATOR

#include "consts.h"
#include "database.h"
#include <openssl/md5.h>
#include <stdlib.h>

int compare_hashes(char *hash_form_file, char *calculated_hash);

int compare_hashes_with_database(char *calculated_hash);

#endif