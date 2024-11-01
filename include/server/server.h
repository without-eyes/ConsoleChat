#ifndef CONSOLECHAT_SERVER_H
#define CONSOLECHAT_SERVER_H

#include "../../include/other/os_directives.h"

#define MAX_USER_COUNT 10

typedef struct {
    SOCKET connectionsArray[MAX_USER_COUNT];
    int connectionsCount;
} Connections;

typedef struct {
    Connections *connections;
    int clientIndex;
} ConnectionsAndClientIndex;

int setupListening(SOCKET *listeningSocket, SOCKADDR_IN socketAddress);

int startServerBroadcast(SOCKET listeningSocket, SOCKADDR_IN socketAddress);

int checkNewConnection(SOCKET newConnectionSocket);

_Noreturn void *receiveAndBroadcastMessages(void *threadData);

void broadcastMessage(const ConnectionsAndClientIndex *threadData, const char *message, int messageSize);

#endif //CONSOLECHAT_SERVER_H
