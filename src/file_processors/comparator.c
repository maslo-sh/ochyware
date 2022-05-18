#include "comparator.h"

int compare_hashes(char *hash_from_file, char *calculated_hash) {
    int comp = 0;

    for (int i = 0; i < SIGNATURE_SIZE; i += 2) {
        char tmp_hash_part[3] = {hash_from_file[i], hash_from_file[i + 1],
                                 '\0'};

        unsigned char rn = (char)strtol(tmp_hash_part, NULL, 0x10);
        unsigned char unsigned_hash_char = calculated_hash[i / 2] < 0
                                               ? calculated_hash[i / 2] + 0x100
                                               : calculated_hash[i / 2];
        comp = rn == unsigned_hash_char ? 1 : -1;
        if (comp == -1) {
            return -1;
        }
    }
    return 1;
}

int compare_hashes_with_database(char *calculated_hash) {
    int res = 0;
    for (int i = 0; i < NUMBER_OF_HASHES; i++) {
        res = compare_hashes(HASH_DB[i], calculated_hash);

        if (res == 1) {
            return 1;
        }
    }

    return -1;
}