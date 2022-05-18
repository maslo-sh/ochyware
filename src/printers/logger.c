#include "logger.h"
#include "log_types.h"

char *strlog_tag(log_conf_t conf) {
    switch (conf.tag) {
    case ERROR:
        return "ERROR";

    case INFO:
        return "INFO";

    case PROMPT:
        return "PROMPT";

    case SUCCESS:
        return "SUCCESS";

    case VIRUS:
        return "VIRUS";

    default:
        return "UNDEFINED_TAG";
    }
}

char *strlog_color(log_conf_t conf) {
    switch (conf.color) {
    case ERR_COLOR:
        return ANSI_COLOR_RED;

    case SUCCESS_COLOR:
        return ANSI_COLOR_GREEN;

    case PROMPT_COLOR:
        return ANSI_COLOR_YELLOW;

    case INFO_COLOR:
        return ANSI_COLOR_CYAN;

    case VIRUS_COLOR:
        return ANSI_COLOR_ORANGE;

    default:
        return "";
    }
}

void logger(log_conf_t conf, char *format, ...) {
    char buffer[256];
    va_list arg_ptr;
    va_start(arg_ptr, format);

    time_t now;
    time(&now);
    char *t = ctime(&now);
    pid_t pid = getpid();

    if (t[strlen(t) - 1] == '\n') {
        t[strlen(t) - 1] = '\0';
    }

    char *str_tag = strlog_tag(conf);
    char *str_col = strlog_color(conf);

    printf("%s ==%d== [%s %s %s]: ", t, pid, str_col, str_tag,
           ANSI_COLOR_WHITE);
    vsnprintf(buffer, 211, format, arg_ptr);
    printf("%s", buffer);
    printf("\n");

    va_end(arg_ptr);
}

void get_log_message(char *buffer, log_conf_t conf, char *format, ...){
    va_list arg_ptr;
    va_start(arg_ptr, format);

    time_t now;
    time(&now);
    char *t = ctime(&now);
    pid_t pid = getpid();

    if (t[strlen(t) - 1] == '\n') {
        t[strlen(t) - 1] = '\0';
    }

    char *str_tag = strlog_tag(conf);
    char *str_col = strlog_color(conf);

    printf("%s ==%d== [%s %s %s]: ", t, pid, str_col, str_tag,
           ANSI_COLOR_WHITE);
    vsnprintf(buffer, 211, format, arg_ptr);
}

void print_perror() { logger(ERR_CONF, "ERRNO: %s", strerror(errno)); }