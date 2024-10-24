#ifndef CONSOLECHAT_CLIENT_H
#define CONSOLECHAT_CLIENT_H

#include <winsock2.h>

typedef struct {
    SOCKET connectionSocket;
} ThreadConnectionSocket;

int setupConnection(SOCKET* connectionSocket, SOCKADDR_IN socketAddress);

_Noreturn void receiveAndPrintMessages(const ThreadConnectionSocket* threadConnectionSocket);

_Noreturn void sendMessage(SOCKET connectionSocket);

void receiveAndSendMessages(SOCKET connectionSocket);

#endif //CONSOLECHAT_CLIENT_H
