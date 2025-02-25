#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define LISTEN_PORT 3256

int main() {
    int sock_listen, sock_accept;
    struct sockaddr_in addr_server, addr_client;
    socklen_t client_size;
    char msg_buffer[256];

    sock_listen = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_listen == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_addr.s_addr = INADDR_ANY;
    addr_server.sin_port = htons(LISTEN_PORT);

    if (bind(sock_listen, (struct sockaddr*)&addr_server, sizeof(addr_server)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(sock_listen, 5);
    printf("Server listening on port %d...\n", LISTEN_PORT);

    client_size = sizeof(addr_client);
    sock_accept = accept(sock_listen, (struct sockaddr*)&addr_client, &client_size);
    if (sock_accept == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(msg_buffer, 0, sizeof(msg_buffer));
        read(sock_accept, msg_buffer, sizeof(msg_buffer));
        printf("Client: %s\n", msg_buffer);
        if (strcmp(msg_buffer, "exit\n") == 0) break;

        printf("Server: ");
        fgets(msg_buffer, sizeof(msg_buffer), stdin);
        write(sock_accept, msg_buffer, strlen(msg_buffer));
    }

    close(sock_accept);
    close(sock_listen);
    return 0;
}
