#include "../../include/client/client.h"
#include "../../include/other/common.h"

int main(int argc, char* argv[]) {
    if (initializeWinsock()) return EXIT_FAILURE;

    SOCKADDR_IN socketAddress;
    setupSocketAddress(&socketAddress);

    SOCKET connectionSocket;
    if (setupConnection(&connectionSocket, socketAddress)) return EXIT_FAILURE;

    receiveAndSendMessages(connectionSocket);

    closesocket(connectionSocket);
    WSACleanup();

    return EXIT_SUCCESS;
}