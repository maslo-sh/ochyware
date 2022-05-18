#ifndef DIR_DIGGER
#define DIR_DIGGER

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void process_files(char* dirname, int indent, void (*func)(char*));
int is_directory(const char *path);

#endif