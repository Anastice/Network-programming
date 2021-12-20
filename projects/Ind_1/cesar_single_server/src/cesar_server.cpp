#include "cesar_server.h"

void handle_connection(SOCKET socket, sockaddr_in *addr) {
    char *str_in_addr = inet_ntoa(addr->sin_addr);
    printf("[%s]>>%s\n", str_in_addr, "Establish new connection");
    int rc = 1;
    while (rc > 0) {
        CesarRequest request;
        memset(&request, sizeof(request), 0);

        CesarResponse response;
        memset(&request, sizeof(response), 0);

        recv(socket, (char *) &request, sizeof(request), 0);
        compute(&request, &response);
        rc = send(socket, (char *) &response, sizeof(response), 0);
    }
    close_socket(socket);
    printf("[%s]>>%s", str_in_addr, "Close incoming connection");
}

CesarResponse *compute(CesarRequest *request, CesarResponse *response) {
    for (int i = 0; i < sizeof(request->textToEncode); ++i) {
        response->encodedText[i] = encode(request->shiftKey, request->textToEncode[i]);
    }
    return response;
}

char encode(int n, char symbol) {
    if (symbol >= 'A' && symbol <= 'Z') {
        symbol = symbol + (n % ENG);
        if (symbol > 'Z') {
            symbol = 'A' + (symbol - 'Z') - 1;
        }
    } else if (symbol >= 'a' && symbol <= 'z') {
        symbol = symbol + (n % ENG);
        if (symbol > 'z') {
            symbol = 'a' + (symbol - 'z') - 1;
        }
    }
//    } else if (symbol >= 'А' && symbol <= 'Я') {
//        symbol = symbol + (n % RUS);
//        if (symbol > 'Я') {
//            symbol = 'А' + (symbol - 'Я') - 1;
//        }
//    } else if (symbol >= 'а' && symbol <= 'я') {
//        symbol = symbol + (n % RUS);
//        if (symbol > 'я') {
//            symbol = 'а' + (symbol - 'я') - 1;
//        }
//    }
    return symbol;
}