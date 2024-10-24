#ifndef CONSOLECHAT_SERVER_H
#define CONSOLECHAT_SERVER_H

#include <winsock2.h>
#define MAX_USER_COUNT 10

typedef struct {
    SOCKET connectionsArray[MAX_USER_COUNT];
    int connectionsCount;
    int currentConnection;
} Connections;

int setupListening(SOCKET* listeningSocket, SOCKADDR_IN socketAddress);

int startServerBroadcast(SOCKET listeningSocket, SOCKADDR_IN socketAddress);

int checkNewConnection(SOCKET newConnectionSocket);

_Noreturn void receiveAndBroadcastMessages(Connections* connections);

void broadcastMessage(const Connections* connections, const char* message, int messageSize);

#endif //CONSOLECHAT_SERVER_H
