#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>

#pragma comment(lib, "ws2_32.lib")

int main(void)
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("Failed to initialize Winsock\n");
        return 1;
    }

    int listenfd = 0;
    int connfd = 0;
    struct sockaddr_in serv_addr;
    char sendBuff[1024];
    int numrv;

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    printf("Socket retrieve success\n");

    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(sendBuff, 0, sizeof(sendBuff));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    if (listen(listenfd, 10) == -1)
    {
        printf("Failed to listen\n");
        return -1;
    }

    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);

        /* Open the file that we wish to transfer */
        FILE* fp;
       if ((fp = fopen("file.txt", "rb")) != 0)
        {
            printf("File open error");
            return 1;
        }

        /* Read data from the file and send it */
        while (1)
        {
            unsigned char buff[256] = { 0 };
            int nread = fread(buff, 1, 256, fp);
            printf("Bytes read %d\n", nread);

            /* If read was successful, send data. */
            if (nread > 0)
            {
                printf("Sending\n");
                send(connfd, (const char*)buff, nread, 0);
            }

            /*
             * There is something tricky going on with read ..
             * Either there was an error, or we reached the end of the file.
             */
            if (nread < 256)
            {
                if (feof(fp))
                    printf("End of file\n");
                if (ferror(fp))
                    printf("Error reading\n");
                break;
            }
        }

        fclose(fp);
        closesocket(connfd);
        Sleep(1000); // Use Sleep instead of sleep on Windows
    }

    closesocket(listenfd);
    WSACleanup();

    return 0;
}
