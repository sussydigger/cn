#include <winsock2.h>
#include <stdio.h>

#define PORT 8080

int main() {
    WSADATA wsa;
    SOCKET sock = 0;
    struct sockaddr_in serv_addr;
    char* hello = "Hello from client";
    char buffer[1024] = {0};

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        perror("WSAStartup failed");
        return 1;
    }

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        perror("Socket creation error");
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 address from text to binary using inet_addr
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (serv_addr.sin_addr.s_addr == INADDR_NONE) {
        perror("Invalid address/ Address not supported");
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed");
        return 1;
    }

    send(sock, hello, strlen(hello), 0);
    printf("Hello message sent\n");
    int valread = recv(sock, buffer, 1024, 0);
    printf("%s\n", buffer);

    // Close the connected socket
    closesocket(sock);

    WSACleanup(); // Cleanup Winsock

    return 0;
}
