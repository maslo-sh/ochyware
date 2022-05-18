#include "printer.h"

void pretty_print_buff(char *buff) {
    unsigned short s_size = strlen(buff);

    printf("\n=========================== BEGIN OF FILE CONTENT "
           "===========================>\n");

    for (int i = 0; i < s_size; i++) {
        printf("%02x", buff[i]);

        if ((i + 1) % GROUP_LIMIT == 0 && (i + 1) % COLUMN_LIMIT != 0) {
            printf("%c", SPACE_CHAR);
        }

        if ((i + 1) % COLUMN_LIMIT == 0) {
            printf("\n");
        }
    }

    printf("\n");

    printf("============================ END OF FILE CONTENT "
           "============================>\n\n");
}

void pretty_print_hash(unsigned char buff[16]) {

    printf("\n================== HASH ==================>\n");

    for (int n = 0; n < 15; n += 2) {
        printf("%02x%02x ", buff[n], buff[n + 1]);
    }

    printf("\n");

    printf("================== HASH ==================>\n\n");
}
