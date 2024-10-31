#ifndef CONSOLECHAT_CLIENT_H
#define CONSOLECHAT_CLIENT_H

#include "../../include/other/os_directives.h"
#define MAX_USERNAME_LENGTH 20

typedef struct {
    SOCKET connectionSocket;
    char* username;
} ClientConnectionData;

void enterUsername(char **username);

int setupConnection(SOCKET* connectionSocket, SOCKADDR_IN socketAddress);

_Noreturn void* receiveAndPrintMessages(void* threadData);

_Noreturn void sendMessage(const ClientConnectionData* clientConnectionData);

void receiveAndSendMessages(SOCKET connectionSocket, const char* username);

#endif //CONSOLECHAT_CLIENT_H
