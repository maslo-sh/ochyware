#include "file_utils.h"
#include <openssl/md5.h>

int read_file_to_buff(char *filename, char **buffer) {
    FILE *infile;
    long numbytes;

    infile = fopen(filename, "rb");
    if (infile == NULL) {
        logger(ERR_CONF, "FILE CANNOT BE OPENED");
        print_perror();
        return -1;
    }

    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    if (numbytes < 0) {
        logger(INFO_CONF, "ERROR WHEN READING FILE SIZE");
        fclose(infile);
        return -1;
    }

    char temp_buff[numbytes + 1];

    fseek(infile, 0L, SEEK_SET);

    if (temp_buff == NULL) {
        logger(ERR_CONF, "MEMORY ERROR");
        print_perror();
        fclose(infile);
        return -1;
    }

    fread(temp_buff, numbytes, 1, infile);

    if (numbytes <= 0){
        logger(INFO_CONF, "EMPTY FILE - SKIPPING");
        fclose(infile);
        return -1;
    }

    temp_buff[numbytes] = '\0';

    fclose(infile);

    *buffer = (char *)malloc(numbytes + 1);
    strncpy(*buffer, temp_buff, numbytes + 1);

    return 0;
}

void remove_trailing_space(char buff[]) {
    int len = strlen(buff);
    int i;

    i = len - 1;
    while (i >= 0 && isspace(buff[i])) {
        buff[i] = '\0';
        i--;
    }
}