#include "../../include/client/client.h"
#include "../../include/other/common.h"
#include "../../include/other/os_directives.h"
#include <stdlib.h>

int main(void) {

#ifdef _WIN32
    if (initializeWinsock()) return EXIT_FAILURE;
#endif

    char *username = "anonymous";
    enterUsername(&username);

    char *ipAddress;
    int port;
    enterIPAddressAndPort(&ipAddress, &port);

    SOCKADDR_IN socketAddress;
    setupSocketAddress(&socketAddress, ipAddress, port);

    SOCKET connectionSocket;
    if (setupConnection(&connectionSocket, socketAddress)) return EXIT_FAILURE;

    receiveAndSendMessages(connectionSocket, username);

    free(username);

#ifdef _WIN32
    closesocket(connectionSocket);
    WSACleanup();
#endif

    return EXIT_SUCCESS;
}