#ifndef PRINTER
#define PRINTER

#include <stdio.h>
#include <string.h>

void pretty_print_buff(char *buff);

void pretty_print_hash(unsigned char buff[16]);

#endif

#define COLUMN_LIMIT 32
#define GROUP_LIMIT 2
#define SPACE_CHAR 0x20
#define NEWLINE_CHAR 0x0a