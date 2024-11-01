#include "../../include/server/server.h"
#include "../../include/other/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int setupListening(SOCKET *listeningSocket, SOCKADDR_IN socketAddress) {
    *listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(*listeningSocket, (SOCKADDR *) &socketAddress, sizeof(socketAddress))) {
        puts("Error: Failed to bind");
        return EXIT_FAILURE;
    }
    listen(*listeningSocket, SOMAXCONN);
    return EXIT_SUCCESS;
}

int startServerBroadcast(const SOCKET listeningSocket, const SOCKADDR_IN socketAddress) {
#ifdef _WIN32
    int socketAddressSize = sizeof(socketAddress);
#elif unix
    unsigned int socketAddressSize = sizeof(socketAddress);
#endif
    Connections *connections = (Connections *) malloc(sizeof(Connections));
    connections->connectionsCount = 0;
    ConnectionsAndClientIndex *threadData = 0;

    for (int i = 0; i < MAX_USER_COUNT; i++) {
        const SOCKET newConnectionSocket = accept(listeningSocket, (SOCKADDR *) &socketAddress, &socketAddressSize);
        if (checkNewConnection(newConnectionSocket)) {
            free(threadData);
            free(connections);
            return EXIT_FAILURE;
        }

        connections->connectionsArray[i] = newConnectionSocket;
        connections->connectionsCount++;

        threadData = malloc(sizeof(ConnectionsAndClientIndex));
        threadData->connections = connections;
        threadData->clientIndex = i;

#ifdef _WIN32
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE) receiveAndBroadcastMessages, (LPVOID) (threadData), 0, 0);
#elif unix
        pthread_t id;
        pthread_create(&id, NULL, receiveAndBroadcastMessages, threadData);
#endif
    }

    free(threadData);
    free(connections);
    return EXIT_SUCCESS;
}

int checkNewConnection(const SOCKET newConnectionSocket) {
    if (newConnectionSocket == 0) {
        puts("Error: Client cant connect to server");
        return EXIT_FAILURE;
    }
    puts("Client successfully connected!");
    return EXIT_SUCCESS;
}

_Noreturn void *receiveAndBroadcastMessages(void *threadData) {
    ConnectionsAndClientIndex *connectionsAndClientIndex = (ConnectionsAndClientIndex *) threadData;
    while (1) {
        char message[MAX_MESSAGE_LENGTH];
        const int bytesReceived = recv(
                connectionsAndClientIndex->connections->connectionsArray[connectionsAndClientIndex->clientIndex],
                message, sizeof(message), 0);
        broadcastMessage(connectionsAndClientIndex, message, bytesReceived);
    }
    free(connectionsAndClientIndex);
}


void broadcastMessage(const ConnectionsAndClientIndex *threadData, const char *message, const int messageSize) {
    for (int i = 0; i < threadData->connections->connectionsCount; i++) {
        if (i == threadData->clientIndex) {
            continue;
        }
        send(threadData->connections->connectionsArray[i], message, messageSize, 0);
    }
}
