#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080  // Port number for the server

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int opt = 1;

    // 1. Create a socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Set socket options to reuse address and port
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }

    // 3. Configure the server address struct
    server_addr.sin_family = AF_INET;            // Use IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;    // Listen on any network interface
    server_addr.sin_port = htons(PORT);          // Convert port to network byte order

    // 4. Bind the socket to the IP and port
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // 5. Start listening for incoming connections (max 5 clients in queue)
    if (listen(server_socket, 5) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("Server listening on port %d...\n", PORT);

    // 6. Accept an incoming connection
    addr_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
    if (client_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("Client connected\n");

    // 7. Receive data from client
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Client: %s\n", buffer);

    // 8. Send response to client
    char response[] = "Message received!";
    send(client_socket, response, sizeof(response), 0);

    // 9. Close sockets
    close(client_socket);
    close(server_socket);

    return 0;
}
