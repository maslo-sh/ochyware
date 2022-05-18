#ifndef THREAD_HANDLER
#define THREAD_HANDLER

#include <pthread.h>

int spawn_thread(void (*callback)());

#endif