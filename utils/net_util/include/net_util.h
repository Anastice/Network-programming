#ifndef NETWORK_PROGRAMMING_COMMON_NET_H
#define NETWORK_PROGRAMMING_COMMON_NET_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>

#ifdef _WIN32

#include <tchar.h>
#include <winsock2.h>
#include <windows.h>
#include <windows.h>
#include <ws2tcpip.h>
typedef int socklen_t;

#define VOID_DEFAULT_RESULT

#elif __linux__

#include<netinet/ip.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netdb.h>

typedef int SOCKET;

#define VOID_DEFAULT_RESULT NULL
#endif

#include "common_util.h"

int common_init_handler();
void common_exit_handler();

int close_socket(int socket);

bool resolve_addr(const char*, in_addr*);
bool parse_cmd(int argc, char* argv[], char* host, short* port);

void error_msg(const char*);

sockaddr_in* init_inet_address(struct sockaddr_in *address, const char*, const short);
int bind_socket_to(SOCKET, struct sockaddr_in*);

#define CHECK_IO(io, err_code, ...) \
if (!(io)) \
{ \
	printf(__VA_ARGS__); \
	printf("\n"); \
	return err_code; \
}

#define CHECK_VOID_IO(io, ...) \
if (!(io))\
{\
	printf(__VA_ARGS__); \
	return VOID_DEFAULT_RESULT; \
}

#define CHECK_SET_OPT(opt_ret, err_msg)\
{\
  if ((opt_ret) != 0)\
  {\
    printf("setsockopt(%s) failed with: %d\n",\
           err_msg, get_last_error());\
    return -1;\
  }\
}

int set_reuse_address(SOCKET, int);
int set_recv_timeout_ms(SOCKET socket, int millis);
int set_group_loopback(SOCKET, int);
int set_group_address(SOCKET, const char *);
int set_group_ttl(SOCKET, int);
int set_loopback(SOCKET, int);

int init_group(const char*, const char*, struct ip_mreq*);
int join_group(SOCKET, struct ip_mreq*);
int leave_group(SOCKET, struct ip_mreq*);
#endif //NETWORK_PROGRAMMING_COMMON_NET_H
