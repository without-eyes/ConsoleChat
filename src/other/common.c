#include "../../include/other/common.h"
#include "../../include/other/os_directives.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32

int initializeWinsock(void) {
    struct WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData)) {
        int error = WSAGetLastError();
        printf("Error: %d", error);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif

void enterIPAddressAndPort(char **ipAddress, int *port) {
    *ipAddress = (char *) malloc(16 * sizeof(char));
    printf("Enter IP address: ");
    fgets(*ipAddress, 16, stdin);
    (*ipAddress)[strcspn(*ipAddress, "\n")] = '\0';
    printf("Enter port: ");
    scanf("%d", port);
    getchar(); // removes additional new line input
}

bool isValidIpAddress(const char *ipAddress) {
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

void setupSocketAddress(SOCKADDR_IN *addr, const char *ipAddress, const int port) {
    addr->sin_addr.s_addr = inet_addr(ipAddress);
    addr->sin_port = htons(port);
    addr->sin_family = AF_INET;
}
