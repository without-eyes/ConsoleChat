#include "../../include/server/server.h"
#include "../../include/other/common.h"
#include <stdio.h>

int setupListening(SOCKET* listeningSocket, SOCKADDR_IN socketAddress) {
    *listeningSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(*listeningSocket, (SOCKADDR*)&socketAddress, sizeof(socketAddress)) != 0) {
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

    for (int i = 0; i < MAX_USER_COUNT; i++) {
        SOCKET newConnectionSocket = accept(listeningSocket, (SOCKADDR*)&socketAddress, &socketAddressSize);
        if (checkNewConnection(newConnectionSocket)) {
            free(connections);
            return EXIT_FAILURE;
        }

        connections->connectionsArray[i] = newConnectionSocket;
        connections->connectionsCount++;
        connections->currentConnection = i;

        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)receiveAndBroadcastMessages, (LPVOID)(connections), 0, 0);
    }

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

_Noreturn void receiveAndBroadcastMessages(Connections* connections) {
    char message[MAX_MESSAGE_LENGTH];
    while (1) {
        recv(connections->connectionsArray[connections->currentConnection], message, sizeof(message), 0);
        broadcastMessage(connections, message, sizeof(message));
    }
}

void broadcastMessage(const Connections* connections, const char* message, const int messageSize) {
    for (int i = 0; i < connections->connectionsCount; i++) {
        if (i == connections->currentConnection) {
            continue;
        }
        int sendResult = send(connections->connectionsArray[i], message, messageSize, 0);
        if (sendResult == -1) {
            perror("Error sending message");
        } else {
            printf("Sent message to client %d: %s\n", i, message);
        }
    }
}