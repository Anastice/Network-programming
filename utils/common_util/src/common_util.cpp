#include "common_util.h"

unsigned long get_tick_count()
{
#ifdef _WIN32
    return GetTickCount();
#elif __linux__
    struct timespec ts;
    unsigned long theTick = 0U;
    clock_gettime(CLOCK_REALTIME, &ts );
    theTick  = ts.tv_nsec / 1000000;
    theTick += ts.tv_sec * 1000;
    return theTick;
#else
#error "Unsupported platform"
#endif
}

ERROR_CODE_TYPE get_last_error() {
#ifdef _WIN32
    return GetLastError();
#elif __linux__
    return errno;
#else
#error "Unsupported platform"
#endif
}

int current_thread_sleep(unsigned int millis) {
#ifdef _WIN32
    Sleep(millis);
    return 0;
#elif __linux__
    return usleep(millis * 1000);
#else
#error "Unsupported platform"
#endif
}
