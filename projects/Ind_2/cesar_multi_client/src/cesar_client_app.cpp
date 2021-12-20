#include "cesar_client.h"

void exit_handler();

void process_response(CesarResponse *rs);

THREAD_RESULT process_connection(void *data) {
    PCLIENT_OPTIONS poptions = (PCLIENT_OPTIONS) data;
    struct sockaddr_in server_addr;
    common_init_handler();
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket <= 0) {
        error_msg("Can't create socket");
        close_socket(client_socket);
        return -1;
    }

    init_inet_address(&server_addr, poptions->server_host, poptions->server_port);
    //Connect to the server
    if (connect(client_socket, (sockaddr *) &server_addr, sizeof(sockaddr))) {
        char err_msg[128] = "";
        sprintf(err_msg, "Can't connect to the server %s:%d", poptions->server_host, poptions->server_port);
        error_msg(err_msg);
        close_socket(client_socket);
        return -1;
    }
    printf("Connection to the server %s:%d success\n",
           poptions->server_host,
           poptions->server_port);

    CesarRequest request;
    request.shiftKey = 4;
    memcpy(request.textToEncode, poptions->data, sizeof(poptions->data));
    {
        printf("Sending %d, %s \n", request.shiftKey, request.textToEncode);
        int sc = send(client_socket, (char *) &request, sizeof(request), 0);
        if (sc <= 0) {
            char err_msg[128] = "";
            sprintf(err_msg, "Can't send data to the server %s:%d", poptions->server_host, poptions->server_port);
            error_msg(err_msg);
            close_socket(client_socket);
            return -1;
        }
    }

    CesarResponse response;
    {
        int sc = recv(client_socket, (char *) &response, sizeof(response), 0);
        if (sc <= 0) {
            char err_msg[128] = "";
            sprintf(err_msg, "Can't receive data from the server %s:%d", poptions->server_host, poptions->server_port);
            error_msg(err_msg);
            close_socket(client_socket);
            return -1;
        }
        process_response(&response);
    }

    close_socket(client_socket);
    return 0;
}

void process_response(CesarResponse *res) {
    printf("Encoded text: %s", res->encodedText);
}
