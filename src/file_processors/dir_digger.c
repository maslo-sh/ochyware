#include "dir_digger.h"
#include "log_types.h"

void process_files(char *dirname, int indent, void (*func)(char *)) {
    int is_dir = is_directory(dirname);
    if (is_dir < 1) {
        logger(ERR_CONF, "%s IS NOT A DIRECTORY", dirname);
        return;
    }

    struct dirent *de;
    DIR *dir = opendir(dirname);

    if (dir == NULL) {
        logger(ERR_CONF, "ERROR WHILE READING DIRECTORY");
        print_perror();
        return;
    }

    while ((de = readdir(dir)) != NULL) {
        char path[1024];
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0 ||
            strcmp(de->d_name, ".git") == 0)
            continue;
        snprintf(path, sizeof(path), "%s/%s", dirname, de->d_name);

        if (de->d_type == DT_DIR) {
            logger(INFO_CONF, "RECURSIVELY ENTERING INTO %s", path);
            process_files(path, indent + 2, func);
        } else {
            logger(INFO_CONF, "ANALYZING %s", path);
            func(path);
        }
    }
    closedir(dir);
    return;
}

int is_directory(const char *path) {
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
        return 0;
    return S_ISDIR(statbuf.st_mode);
}