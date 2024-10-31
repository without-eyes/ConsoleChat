#include "../../include/server/server.h"
#include "../../include/other/common.h"
#include <stdlib.h>

int main(void) {
#ifdef _WIN32
    if (initializeWinsock()) return EXIT_FAILURE;
#endif

    char *ipAddress;
    int port;
    enterIPAddressAndPort(&ipAddress, &port);

    SOCKADDR_IN socketAddress;
    setupSocketAddress(&socketAddress, ipAddress, port);

    SOCKET listeningSocket;
    if (setupListening(&listeningSocket, socketAddress)) return EXIT_FAILURE;

    if (startServerBroadcast(listeningSocket, socketAddress)) return EXIT_FAILURE;

#ifdef _WIN32
    closesocket(connectionSocket);
    WSACleanup();
#endif

    return EXIT_SUCCESS;
}