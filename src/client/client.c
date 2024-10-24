#include "../../include/client/client.h"
#include "../../include/other/common.h"
#include <stdio.h>
#include <unistd.h>

int setupConnection(SOCKET* connectionSocket, const SOCKADDR_IN socketAddress) {
    *connectionSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(*connectionSocket, (SOCKADDR*)&socketAddress, sizeof(socketAddress)) != 0) {
        puts("Error: Failed connect to server");
        return EXIT_FAILURE;
    } else {
        puts("Connected!");
        return EXIT_SUCCESS;
    }
}

_Noreturn void receiveAndPrintMessages(const ThreadConnectionSocket* threadConnectionSocket) {
    char message[MAX_MESSAGE_LENGTH];
    while (1) {
        recv(threadConnectionSocket->connectionSocket, message, sizeof(message), 0);
        printf("%s", message);
    }
}

void sendMessage(const SOCKET connectionSocket) {
    char message[MAX_MESSAGE_LENGTH];
    while (1) {
        fgets(message, sizeof(message), stdin);
        send(connectionSocket, message, sizeof(message), 0);
        sleep(1);
    }
}

void receiveAndSendMessages(const SOCKET connectionSocket) {
    ThreadConnectionSocket* threadConnectionSocket = (ThreadConnectionSocket*)malloc(sizeof(ThreadConnectionSocket));
    threadConnectionSocket->connectionSocket = connectionSocket;
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) receiveAndPrintMessages, (LPVOID)(threadConnectionSocket), 0, 0);
    sendMessage(connectionSocket);
}