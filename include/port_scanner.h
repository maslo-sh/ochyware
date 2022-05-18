#ifndef PORT_SCANNER
#define PORT_SCANNER

#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include "log_types.h"

int launch_port_scanner();

#endif
