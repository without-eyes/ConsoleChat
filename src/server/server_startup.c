#include "../../include/server/server.h"
#include "../../include/other/common.h"

int main(int argc, char* argv[]) {
    if (initializeWinsock()) return EXIT_FAILURE;

    char *ipAddress;
    int port;
    enterIPAddressAndPort(&ipAddress, &port);

    SOCKADDR_IN socketAddress;
    setupSocketAddress(&socketAddress, ipAddress, port);

    SOCKET listeningSocket;
    if (setupListening(&listeningSocket, socketAddress)) return EXIT_FAILURE;

    if (startServerBroadcast(listeningSocket, socketAddress)) return EXIT_FAILURE;

    closesocket(listeningSocket);
    WSACleanup();

    return EXIT_SUCCESS;
}