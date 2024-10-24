#include "../../include/server/server.h"
#include "../../include/other/common.h"

int main(int argc, char* argv[]) {
    if (initializeWinsock()) return EXIT_FAILURE;

    SOCKADDR_IN socketAddress;
    setupSocketAddress(&socketAddress);

    SOCKET listeningSocket;
    if (setupListening(&listeningSocket, socketAddress)) return EXIT_FAILURE;

    if (startServerBroadcast(listeningSocket, socketAddress)) return EXIT_FAILURE;

    closesocket(listeningSocket);
    WSACleanup();

    return EXIT_SUCCESS;
}