#include "thread_handler.h"

int spawn_thread(void (*callback)()) {
    pthread_t thread;

    int err = pthread_create(&thread, NULL, callback, NULL);

    if (err != 0) {
        print_perror();
        return -1;
    }

    pthread_join(thread, NULL);
}