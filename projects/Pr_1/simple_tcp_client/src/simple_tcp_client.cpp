#include "simple_tcp_client.h"

void exit_handler();

SOCKET client_socket;

int main(int argc, char *argv[]) {
    atexit(exit_handler);
    atexit(common_exit_handler);

    short port;
    char host[128] = "";
    bool parse_cmd_result = parse_cmd(argc, argv, host, &port);

    if (!parse_cmd_result || !host || !strlen(host)) {
        printf("Invalid host or port. Usage %s -h host -p port\n", argv[0]);
        return -1;
    }

    common_init_handler();

    client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket <= 0) {
        error_msg("Can't create socket");
        return -1;
    }

    struct sockaddr_in server_addr;
    init_inet_address(&server_addr, host, port);

    //Connect to the server
    if (connect(client_socket, (sockaddr *) &server_addr, sizeof(sockaddr))) {
        char err_msg[128] = "";
        sprintf(err_msg, "Can't connect to the server %s:%d", host, port);
        error_msg(err_msg);
        return -1;
    }

    printf("Connection to the server %s:%d success\n", host, port);
    char msg[256] = "";
    do {
        printf("%s", "Enter msg:");
        scanf("%[^\n]s", msg);
        scanf("%*c");
        int sc = send(client_socket, msg, sizeof(msg), 0);
        if (sc <= 0) {
            char err_msg[128] = "";
            sprintf(err_msg, "Can't send data to the server %s:%d", host, port);
            error_msg(err_msg);
            return -1;
        }
    } while (strcmp(msg, "exit") != 0);
    return 0;
}

void exit_handler() {
    close_socket(client_socket);
}
