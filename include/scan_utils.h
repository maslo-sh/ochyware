#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <openssl/md5.h>
#include <unistd.h>
#include "consts.h"
#include "log_types.h"
#include "database.h"

extern int loops;
extern DETECTED_VIRUSES;
extern int SCANNED_FILES;

void process_file_unit(char *filename);