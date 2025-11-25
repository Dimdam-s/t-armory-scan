```c
#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/time.h>
    #define SOCKET int
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
#endif

#include <stdio.h>
#include <stdlib.h>

#define ERROR -1

void cleanup_sockets() {
#ifdef _WIN32
    WSACleanup();
#endif
}

int main(int ac, char **av)
{
#ifdef _WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed.\n");
        return 1;
    }
#endif

    if (ac != 2)
    {
        printf("ERROR | Respectez le format --> \"0.0.0.0\" \n");
        cleanup_sockets();
        exit(EXIT_FAILURE);
    } 

    for (int i = 0; i <= 1024; i++)
    {
        SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
        struct sockaddr_in target;
        
#ifdef _WIN32
        DWORD timeout = 2000; // 2 seconds in milliseconds
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));
#else
        struct timeval timeout;
        timeout.tv_sec = 2; 
        timeout.tv_usec = 0;
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
#endif

        if (sock == INVALID_SOCKET) {
            cleanup_sockets();
            exit(EXIT_FAILURE);
        }

        target.sin_family = AF_INET;
        target.sin_port = htons(i);
        target.sin_addr.s_addr = inet_addr(av[1]); 
    
        int resultat = connect(sock, (struct sockaddr *)&target, sizeof(target));

        if (resultat == 0)
        {
            char buffer[2024] = {0};
            int n = recv(sock, buffer, sizeof(buffer), 0);

            if (n > 0)
                printf("-- Port %d OPEN --\n %s", i, buffer);
            else if (n == -1 || n == 0)
                printf("-- Port %d OPEN ( silencieux ) --\n", i);

        }

#ifdef _WIN32
        closesocket(sock);
#else
        close(sock);
#endif
    }
    
    cleanup_sockets();
    return(EXIT_SUCCESS);
}
```