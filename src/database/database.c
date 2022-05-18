#include "database.h"

char **HASH_DB;
int NUMBER_OF_HASHES;

int read_hash_database(char *filename) {

    char *buffer = NULL;

    int res = read_file_to_buff(filename, &buffer);

    if (res == -1) {
        return -1;
    }

    int buff_it = 0;

    NUMBER_OF_HASHES = strlen(buffer) / SIGNATURE_SIZE;

    HASH_DB = (char **)malloc(NUMBER_OF_HASHES * sizeof(char *));
    for (int i = 0; i < NUMBER_OF_HASHES; i++)
        HASH_DB[i] = (char *)malloc(SIGNATURE_SIZE * sizeof(char));

    for (int i = 0; i < NUMBER_OF_HASHES; i++) {
        for (int j = 0; j < SIGNATURE_SIZE; j++) {
            HASH_DB[i][j] = buffer[buff_it];
            buff_it++;
        }
        buff_it++;
    }

    logger(SUCCESS_CONF, "HASH DATABASE SUCCESSFULLY LOADED");

    free(buffer);
}

int deallocate_db_memory() {
    logger(INFO_CONF, "DEALLOCATING HASH DATABASE MEMORY");
    for (int i = 0; i < NUMBER_OF_HASHES; i++)
        free(HASH_DB[i]);

    free(HASH_DB);
}