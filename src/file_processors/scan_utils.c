#include "scan_utils.h"

void process_file_unit(char *filename) {
    int is_dir = is_directory(filename);

    if (is_dir == 1) {
        logger(ERR_CONF, "%s IS NOT A FILE", filename);
        return;
    }

    char *buffer = NULL;
    char *digest = (char *)malloc(MD5_DIGEST_LENGTH);

    int rfile_res = read_file_to_buff(filename, &buffer);

    if (rfile_res < 0) {
        logger(ERR_CONF, "FILE %s CANNOT BE OPENED", filename);
        print_perror();
        free(digest);
        free(buffer);
        return;
    }

    logger(SUCCESS_CONF, "FILE %s SUCCESSFULLY LOADED TO THE BUFFER", filename);

    pretty_print_buff(buffer);
    logger(INFO_CONF, "CALCULATING HASH FOR FILE %s", filename);
    hash_buffer(buffer, strlen(buffer), digest);
    pretty_print_hash(digest);

    logger(INFO_CONF, "COMPARING HASH OF %s WITH HASHES FROM DATABASE",
           filename);
    int are_equal = compare_hashes_with_database(digest);
    if (are_equal == 1) {
        int rand_shift = rand();
        logger(VIRUS_CONF, "!!! %s - VIRUS DETECTED !!!", filename);
        DETECTED_VIRUSES++;
        int encryption_res = encrypt_file(filename, rand_shift);

        if (encryption_res < 0){
            logger(ERR_CONF, "FAILED TO ENCRYPT DANGEROUS FILE");
        }
    }
    SCANNED_FILES++;
    logger(INFO_CONF, "DEALLOCATING MEMORY");
    free(buffer);
    free(digest);
}