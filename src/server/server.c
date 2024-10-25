#include "../../include/server/server.h"
#include "../../include/other/common.h"
#include <stdio.h>

int setupListening(SOCKET* listeningSocket, SOCKADDR_IN socketAddress) {
    *listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(*listeningSocket, (SOCKADDR*)&socketAddress, sizeof(socketAddress))) {
        puts("Error: Failed to bind");
        return EXIT_FAILURE;
    } else {
        listen(*listeningSocket, SOMAXCONN);
        return EXIT_SUCCESS;
    }
}

int startServerBroadcast(const SOCKET listeningSocket, const SOCKADDR_IN socketAddress) {
    int socketAddressSize = sizeof(socketAddress);
    Connections* connections = (Connections*)malloc(sizeof(Connections));
    connections->connectionsCount = 0;
    ThreadData* threadData;

    for (int i = 0; i < MAX_USER_COUNT; i++) {
        SOCKET newConnectionSocket = accept(listeningSocket, (SOCKADDR*)&socketAddress, &socketAddressSize);
        if (checkNewConnection(newConnectionSocket)) {
            free(threadData);
            free(connections);
            return EXIT_FAILURE;
        }

        connections->connectionsArray[i] = newConnectionSocket;
        connections->connectionsCount++;

        // Create a struct to pass the specific client index
        threadData = malloc(sizeof(ThreadData));
        threadData->connections = connections;
        threadData->clientIndex = i;

        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)receiveAndBroadcastMessages, (LPVOID)(threadData), 0, 0);
    }

    free(threadData);
    free(connections);
    return EXIT_SUCCESS;
}

int checkNewConnection(SOCKET newConnectionSocket) {
    if (newConnectionSocket == 0) {
        puts("Error: Client cant connect to server");
        return EXIT_FAILURE;
    } else {
        puts("Client successfully connected!");
        return EXIT_SUCCESS;
    }
}

_Noreturn void receiveAndBroadcastMessages(ThreadData* threadData) {
    char message[MAX_MESSAGE_LENGTH];
    while (1) {
        recv(threadData->connections->connectionsArray[threadData->clientIndex], message, sizeof(message), 0);
        broadcastMessage(threadData, message, sizeof(message));
    }
    free(threadData);
}


void broadcastMessage(const ThreadData* threadData, const char* message, const int messageSize) {
    for (int i = 0; i < threadData->connections->connectionsCount; i++) {
        if (i == threadData->clientIndex) {
            continue;
        }
        send(threadData->connections->connectionsArray[i], message, messageSize, 0);
    }
}
