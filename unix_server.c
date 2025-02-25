#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_FILE "/tmp/unix_socket_3256"

int main() {
    int sock_server, sock_connection;
    struct sockaddr_un addr_server, addr_client;
    socklen_t client_addr_len;
    char msg_buffer[256];

    sock_server = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_server == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    addr_server.sun_family = AF_UNIX;
    strcpy(addr_server.sun_path, SOCKET_FILE);
    unlink(SOCKET_FILE);

    if (bind(sock_server, (struct sockaddr*)&addr_server, sizeof(addr_server)) == -1) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    listen(sock_server, 5);
    printf("Server listening on UNIX socket...\n");

    client_addr_len = sizeof(addr_client);
    sock_connection = accept(sock_server, (struct sockaddr*)&addr_client, &client_addr_len);
    if (sock_connection == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(msg_buffer, 0, sizeof(msg_buffer));
        read(sock_connection, msg_buffer, sizeof(msg_buffer));
        printf("Client: %s\n", msg_buffer);
        if (strcmp(msg_buffer, "exit") == 0) break;

        printf("Server: ");
        fgets(msg_buffer, sizeof(msg_buffer), stdin);
        write(sock_connection, msg_buffer, strlen(msg_buffer));
    }

    close(sock_connection);
    close(sock_server);
    unlink(SOCKET_FILE);
    return 0;
}
