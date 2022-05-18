#include "hasher.h"
#include "consts.h"
#include "log_types.h"

void hash_buffer(char *buffer, int s_size, char *out) {
    int n;
    MD5_CTX c;
    unsigned char digest[MD5_DIGEST_LENGTH];

    logger(INFO_CONF, "INITIALIZING MD5 CONTEXT");
    MD5_Init(&c);

    int hashing_part = 0;
    int total_hahing_parts = s_size / 512 + (s_size % 512 > 0 ? 1 : 0);

    while (s_size > 0) {
        hashing_part++;
        if (s_size > 512) {
            logger(INFO_CONF, "HASHING PART OF A BUFFER (%d/%d)", hashing_part,
                   total_hahing_parts);
            MD5_Update(&c, buffer, 512);
        } else {
            logger(INFO_CONF, "HASHING PART OF A BUFFER (%d/%d)", hashing_part,
                   total_hahing_parts);
            MD5_Update(&c, buffer, s_size);
        }
        s_size -= 512;
        buffer += 512;
    }

    MD5_Final(digest, &c);

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        out[i] = digest[i];
    }

    logger(SUCCESS_CONF, "HASHING FINISHED");
}