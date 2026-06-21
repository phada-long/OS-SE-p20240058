/* server.c — Simple TCP server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "Hello from server!";

    /* 1. Create a socket descriptor */
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    printf("Server: socket created successfully (fd=%d)\n", server_fd);

    /* Allow quick port reuse to prevent "Address already in use" errors */
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    /* 2. Set up address configuration */
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; 
    address.sin_port = htons(PORT);

    /* 3. Bind socket to the specified network port */
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server: bound successfully to port %d\n", PORT);

    /* 4. Listen for incoming client connection handshakes */
    if (listen(server_fd, 1) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server: listening... waiting for a client to connect.\n");

    /* 5. Accept connection blocks until a client finishes the handshake */
    client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
    if (client_fd < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    printf("Server: client handshake complete. Connected!\n");

    /* 6. Read raw payload message from client stream buffer */
    int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0';
        printf("Server: received from client: \"%s\"\n", buffer);
    }

    /* 7. Send a response acknowledgment text string back to client */
    send(client_fd, response, strlen(response), 0);
    printf("Server: sent response: \"%s\"\n", response);

    /* 8. Close connections and release system resource handles */
    close(client_fd);
    close(server_fd);
    printf("Server: connection shutdown.\n");

    return 0;
}
