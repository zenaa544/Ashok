#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080  // Server port number

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 1. Create a socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 2. Configure server address struct
    server_addr.sin_family = AF_INET;             // Use IPv4
    server_addr.sin_port = htons(PORT);           // Convert port to network byte order

    // Convert human-readable IP to binary form using inet_pton
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
        perror("Invalid address/ Address not supported");
        exit(EXIT_FAILURE);
    }

    // 3. Connect to the server
    if (connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to the server\n");

    // 4. Send data to the server
    char message[] = "Hello Server!";
    send(client_socket, message, sizeof(message), 0);

    // 5. Receive response from server
    recv(client_socket, buffer, sizeof(buffer), 0);
    printf("Server: %s\n", buffer);

    // 6. Close the socket
    close(client_socket);

    return 0;
}
