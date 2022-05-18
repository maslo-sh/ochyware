#include "encryptor.h"

int encrypt_file(char *filename, int shift) {
    char ch;
    FILE *fpts, *fptt;

    fpts = fopen(filename, "r");
    if (fpts == NULL) {
        printf("ERROR WHEN OPENING");
        print_perror("Problem ");
        return -1;
    }
    fptt = fopen("temp.txt", "w");
    if (fptt == NULL) {
        printf("ERROR WHEN CREATING A FILE");
        print_perror("Problem ");
        fclose(fpts);
        return -1;
    }
    while (1) {
        ch = fgetc(fpts);
        if (ch == EOF) {
            break;
        } else {
            ch = ch + shift;
            fputc(ch, fptt);
        }
    }
    fclose(fpts);
    fclose(fptt);
    fpts = fopen(filename, "w");
    if (fpts == NULL) {
        printf("ERROR WHEN OPENING");
        print_perror("Problem ");
        return -1;
    }
    fptt = fopen("temp.txt", "r");
    if (fptt == NULL) {
        printf("ERROR WHEN OPENING");
        print_perror("Problem ");
        fclose(fpts);
        return -1;
    }
    while (1) {
        ch = fgetc(fptt);
        if (ch == EOF) {
            break;
        } else {
            fputc(ch, fpts);
        }
    }

    if (remove("temp.txt") != 0){
        logger(ERR_CONF, "FAILED TO REMOVE TEMPORARY FILE");
    }
    logger(SUCCESS_CONF, "FILE %s ENCRYPTED", filename);
    fclose(fpts);
    fclose(fptt);
}