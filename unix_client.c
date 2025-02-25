#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_FILE "/tmp/unix_socket_3256"

int main() {
    int sock_client;
    struct sockaddr_un addr_server;
    char msg_buffer[256];

    sock_client = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_client == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    addr_server.sun_family = AF_UNIX;
    strcpy(addr_server.sun_path, SOCKET_FILE);

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
