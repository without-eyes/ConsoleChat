#ifndef CONSOLECHAT_SERVER_H
#define CONSOLECHAT_SERVER_H

#include <winsock2.h>
#define MAX_USER_COUNT 10

typedef struct {
    SOCKET connectionsArray[MAX_USER_COUNT];
    int connectionsCount;
} Connections;

typedef struct {
    Connections* connections;
    int clientIndex;
} ThreadData;

int setupListening(SOCKET* listeningSocket, SOCKADDR_IN socketAddress);

int startServerBroadcast(SOCKET listeningSocket, SOCKADDR_IN socketAddress);

int checkNewConnection(SOCKET newConnectionSocket);

_Noreturn void receiveAndBroadcastMessages(ThreadData* threadData);

void broadcastMessage(const ThreadData* threadData, const char* message, const int messageSize);

#endif //CONSOLECHAT_SERVER_H
