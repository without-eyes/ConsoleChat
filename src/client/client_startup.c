#include "../../include/client/client.h"
#include "../../include/other/common.h"

int main(int argc, char* argv[]) {
    if (initializeWinsock()) return EXIT_FAILURE;

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
    closesocket(connectionSocket);
    WSACleanup();

    return EXIT_SUCCESS;
}