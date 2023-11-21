#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed to initialize Winsock\n");
        return 1;
    }

    int sockfd = 0;
    int bytesReceived = 0;
    char recvBuff[256];
    memset(recvBuff, 0, sizeof(recvBuff));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket retrieve success\n");

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    // Use inet_addr to convert IP address
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
    {
        printf("Error: Connect Failed\n");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    FILE* fp;
   if ((fp = fopen("file.txt", "rb")) != 0)
    {
        printf("Error opening file");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }

    while ((bytesReceived = recv(sockfd, recvBuff, 256, 0)) > 0)
    {
        printf("Bytes received %d\n", bytesReceived);
        fwrite(recvBuff, 1, bytesReceived, fp);
    }

    if (bytesReceived < 0)
    {
        printf("Read Error\n");
    }

    fclose(fp);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
