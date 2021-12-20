#ifndef NETWORK_PROGRAMMING_COMMON_UTILS_H
#define NETWORK_PROGRAMMING_COMMON_UTILS_H

#ifdef _WIN32

#include <windows.h>

typedef DWORD ERROR_CODE_TYPE;

#ifndef ERROR_TIMEOUT
 #define ERROR_TIMEOUT WSAETIMEDOUT
#endif

#elif __linux__

#include <errno.h>
#include <time.h>
#include <unistd.h>

typedef int ERROR_CODE_TYPE;

#define ERROR_TIMEOUT ETIMEDOUT

#else
#error "Unsupported platform"
#endif

unsigned long get_tick_count();

ERROR_CODE_TYPE get_last_error();

int current_thread_sleep(unsigned int millis);

#endif //NETWORK_PROGRAMMING_COMMON_UTILS_H
