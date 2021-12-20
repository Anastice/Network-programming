#ifndef NETWORK_PROGRAMMING_SIMPLE_TCP_CLIENT_H
#define NETWORK_PROGRAMMING_SIMPLE_TCP_CLIENT_H
#define ENG 26
#define RUS 32

#include "net_util.h"
#include "thread_util.h"
#include "shared_tcp_structs.h"

#include <vector>

THREAD_RESULT process_connection(void *data);

typedef struct tagClientOptions {
    char server_host[128];
    short server_port;
    char data[255];
} CLIENT_OPTIONS, *PCLIENT_OPTIONS;


#endif //NETWORK_PROGRAMMING_SIMPLE_TCP_CLIENT_H