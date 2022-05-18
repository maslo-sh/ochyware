#ifndef SERVER_SOCKET
#define SERVER_SOCKET

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

void read_from_client(int socket_fd, char socket_buff[], int length);

void handle(int socket_fd);

#endif