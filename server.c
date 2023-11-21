#include <winsock2.h>
#include <stdio.h>

#define PORT 8080

int main() {
    
    WSADATA wsa;
    SOCKET server_fd, new_socket;
    struct sockaddr_in server, client;
    int addrlen = sizeof(client);
    char buffer[1024] = {0};
    const char* hello = "Hello from server";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("socket failed");
        return 1;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind the socket
    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR) {
        perror("bind failed");
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) == SOCKET_ERROR) {
        perror("listen");
        return 1;
    }

    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&client, &addrlen)) == INVALID_SOCKET) {
        perror("accept");
        return 1;
    }

    int valread = recv(new_socket, buffer, 1024, 0);
    printf("%s\n", buffer);

    send(new_socket, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // Close the connected socket
    closesocket(new_socket);
    // Close the listening socket
    closesocket(server_fd);

    WSACleanup(); // Cleanup Winsock

    return 0;
}
