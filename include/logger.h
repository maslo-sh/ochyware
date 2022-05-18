#ifndef LOGGER_H
#define LOGGER_H

#include "log_types.h"
#include "colors.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdarg.h>
#include <errno.h>

void logger(log_conf_t conf, char *format, ...);

void get_log_message(char *buffer, log_conf_t conf, char *format, ...);

void print_perror();

char *strlog_tag(log_conf_t conf);

char *strlog_color(log_conf_t conf);

void reset_output(void);


#endif