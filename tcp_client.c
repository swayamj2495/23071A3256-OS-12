#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_PORT 3256
#define SERVER_ADDRESS "127.0.0.1"

int main() {
    int sock_client;
    struct sockaddr_in addr_server;
    char msg_buffer[256];

    sock_client = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_client == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(SERVER_PORT);
    addr_server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

    if (connect(sock_client, (struct sockaddr*)&addr_server, sizeof(addr_server)) == -1) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Client: ");
        fgets(msg_buffer, sizeof(msg_buffer), stdin);
        write(sock_client, msg_buffer, strlen(msg_buffer));

        if (strcmp(msg_buffer, "exit\n") == 0) break;

        memset(msg_buffer, 0, sizeof(msg_buffer));
        read(sock_client, msg_buffer, sizeof(msg_buffer));
        printf("Server: %s\n", msg_buffer);
    }

    close(sock_client);
    return 0;
}
