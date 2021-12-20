#include "cesar_client.h"

std::vector<THREAD_HANDLE> connection_pool;

int main(int argc, char *argv[]) {
    atexit(common_exit_handler);
    short server_port;
    char server_host[128] = "";
    bool parse_cmd_result = parse_cmd(argc, argv, server_host, &server_port);

    if (!parse_cmd_result || !server_host || !strlen(server_host)) {
        printf("Invalid server_host or server_port. Usage %s -h server_host -p server_port\n", argv[0]);
        return -1;
    }
    common_init_handler();

    const int count_clients = 2;
    char messages[count_clients][64] = {"Hello world", "Hello world"};
    CLIENT_OPTIONS options[count_clients];
    for (int i = 0; i < count_clients; ++i) {
        PCLIENT_OPTIONS poptions = &options[i];
        strcpy(poptions->server_host, server_host);
        poptions->server_port = server_port;
        strcpy(poptions->data, "Hello world");
        connection_pool.push_back(
                create_thread(process_connection, poptions)
        );
    }
    wait_thread(connection_pool.data(), connection_pool.size());

    return 0;
}
