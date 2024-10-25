#ifndef CONSOLECHAT_CLIENT_H
#define CONSOLECHAT_CLIENT_H

#include <winsock2.h>
#define MAX_USERNAME_LENGTH 20

typedef struct {
    SOCKET connectionSocket;
    char* username;
} ClientConnectionData;

void enterUsername(char **username);

int setupConnection(SOCKET* connectionSocket, SOCKADDR_IN socketAddress);

_Noreturn void receiveAndPrintMessages(const ClientConnectionData* clientConnectionData);

_Noreturn void sendMessage(const ClientConnectionData* clientConnectionData);

void receiveAndSendMessages(SOCKET connectionSocket, const char* username);

#endif //CONSOLECHAT_CLIENT_H
