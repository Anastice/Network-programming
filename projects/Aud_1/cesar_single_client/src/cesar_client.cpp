#include "cesar_client.h"

void exit_handler();

SOCKET client_socket;

void process_response(CesarResponse *);

int main(int argc, char *argv[]) {
    atexit(common_exit_handler);
    atexit(exit_handler);

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

    CesarRequest request;
    CesarResponse response;
    {
        printf("%s\n", "Enter shit key");
        scanf("%d", &request.shiftKey);
        getchar();
        printf("%s\n", "Enter text to encode");
        scanf("%[^\n]s", request.textToEncode);
        scanf("%*c");
        int sc = send(client_socket, (char *) &request, sizeof(request), 0);
        if (sc <= 0) {
            char err_msg[128] = "";
            sprintf(err_msg, "Can't send data to the server %s:%d", host, port);
            error_msg(err_msg);
            return -1;
        }
    }

    {
        int sc = recv(client_socket, (char *) &response, sizeof(response), 0);
        if (sc <= 0) {
            char err_msg[128] = "";
            sprintf(err_msg, "Can't received data from the server %s:%d", host, port);
            error_msg(err_msg);
            return -1;
        }

        process_response(&response);
    }

    return 0;
}

void process_response(CesarResponse *res) {
    printf("Encoded text: %s", res->encodedText);
}

void exit_handler() {
    close_socket(client_socket);
}
