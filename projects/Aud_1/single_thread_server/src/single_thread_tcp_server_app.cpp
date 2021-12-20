#include "single_thread_tcp_server.h"

void exit_handler();

SOCKET server_socket;

int main(int argc, char *argv[]) {
    atexit(exit_handler);
    atexit(common_exit_handler);

    short port = DEFAULT_PORT;
    char host[128] = "";
    common_init_handler();

    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket <= 0) {
        error_msg("Can't create socket");
        return -1;
    }

    sockaddr_in server_addr;
    init_inet_address(&server_addr, host, port);

    //Bind socket to the address on the server
    if (bind(server_socket, (sockaddr *) &server_addr, sizeof(sockaddr))) {
        char err_msg[128] = "";
        sprintf(err_msg, "Can't bind socket to the port %d", port);
        error_msg(err_msg);
        return -1;
    }

    if (listen(server_socket, CONNECTION_QUEUE)) {
        error_msg("Error listening socket");
        return -1;
    }

    printf("Server running at the port %d\n", port);

    while (true) {
        sockaddr_in incom_addr;
        memset(&incom_addr, 0, sizeof(incom_addr));
        socklen_t len = sizeof(incom_addr);
        SOCKET socket = accept(server_socket, (sockaddr *) &incom_addr, &len);
        if (socket <= 0) {
            error_msg("Can't accept connection");
            return -1;
        }
        handle_connection(socket, &incom_addr);
    }
    close_socket(server_socket);

    return 0;
}

void exit_handler() {
    close_socket(server_socket);
}