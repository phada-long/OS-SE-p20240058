/* client.c — Simple TCP client */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    const char *message = "Hello from client!";

    /* 1. Create a client socket descriptor */
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Client: socket created successfully\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    /* Convert local IPv4 address text representation to native network binary format */
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("inet_pton address conversion failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }

    /* 2. Execute connection request handshake to target listening server */
    printf("Client: connecting to server on port %d...\n", PORT);
    if (connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sock_fd);
        exit(EXIT_FAILURE);
    }
    printf("Client: connection established!\n");

    /* 3. Send out payload message byte string onto connection stream */
    send(sock_fd, message, strlen(message), 0);
    printf("Client: sent message: \"%s\"\n", message);

    /* 4. Await response message back from server descriptor interface */
    int bytes_read = read(sock_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Client: received from server: \"%s\"\n", buffer);
    }

    /* 5. Close connection handle */
    close(sock_fd);
    printf("Client: connection closed.\n");

    return 0;
}
