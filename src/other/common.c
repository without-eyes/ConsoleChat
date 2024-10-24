#include "../../include/other/common.h"
#include <stdio.h>

int initializeWinsock() {
    struct WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData)) {
        int error = WSAGetLastError();
        printf("Error: %d", error);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void setupSocketAddress(SOCKADDR_IN* addr) {
    addr->sin_addr.s_addr = inet_addr("127.0.0.1");
    addr->sin_port = htons(1111);
    addr->sin_family = AF_INET;
}
