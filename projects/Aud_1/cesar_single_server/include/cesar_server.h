#ifndef NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H
#define NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H

#include "net_util.h"
#include "shared_tcp_structs.h"
#include "math.h"

#define DEFAULT_PORT 5559
#define CONNECTION_QUEUE 100
#define ENG 26
#define RUS 32

CesarResponse *compute(CesarRequest *request, CesarResponse *response);

char encode(int n, char symbol);

void handle_connection(SOCKET, sockaddr_in *);

#endif //NETWORK_PROGRAMMING_SINGLE_THREAD_TCP_SERVER_H
