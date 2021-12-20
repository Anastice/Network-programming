#include "single_thread_tcp_server.h"

void handle_connection(SOCKET socket, sockaddr_in* addr) {
    char* str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");
    while (true) {
        char buffer[256] = "";
        int rc = recv(socket, buffer, sizeof(buffer), 0);
        if (rc > 0) {
            printf("[%s]:%s\n", str_in_addr, buffer);
        }
        else {
            break;
        }
    }
    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, "Close incoming connection");
}