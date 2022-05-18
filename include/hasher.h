#ifndef HASHER
#define HASHER

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/md5.h>

void hash_buffer(char *buff, int length, char *out);

#endif