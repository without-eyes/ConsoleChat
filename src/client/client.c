#include "../../include/client/client.h"
#include "../../include/other/common.h"
#include <stdio.h>
#include <unistd.h>

void enterUsername(char **username) {
    printf("Enter your username(or skip by pressing 'Enter'): ");
    char *inputtedUsername = (char*)malloc(MAX_USERNAME_LENGTH * sizeof(char));
    fgets(inputtedUsername, MAX_USERNAME_LENGTH, stdin);
    inputtedUsername[strcspn(inputtedUsername, "\n")] = '\0';
    if (strcmp(inputtedUsername, "") != 0) {
        *username = inputtedUsername;
    } else {
        free(inputtedUsername);
    }
}

int setupConnection(SOCKET* connectionSocket, const SOCKADDR_IN socketAddress) {
    *connectionSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(*connectionSocket, (SOCKADDR*)&socketAddress, sizeof(socketAddress))) {
        puts("Error: Failed connect to server");
        return EXIT_FAILURE;
    } else {
        puts("Connected!");
        return EXIT_SUCCESS;
    }
}

_Noreturn void receiveAndPrintMessages(const ClientConnectionData* clientConnectionData) {
    char message[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH + 4];
    while (1) {
        int bytesReceived = recv(clientConnectionData->connectionSocket, message, sizeof(message), 0);
        if (bytesReceived > 0) {
            message[bytesReceived] = '\0';
            message[strcspn(message, "\n")] = '\0';
            printf("\33[2K\r%s\n", message);
            printf("[%s] ", clientConnectionData->username);
            fflush(stdout);
        }
    }
}

void sendMessage(const ClientConnectionData* clientConnectionData) {
    char message[MAX_MESSAGE_LENGTH];
    char formattedMessage[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH + 4];

    while (1) {
        printf("[%s] ", clientConnectionData->username);
        fflush(stdout);
        if (gets(message) != NULL) {
            message[strcspn(message, "\n")] = '\0';
            snprintf(formattedMessage, sizeof(formattedMessage), "[%s] %s", clientConnectionData->username, message);
            send(clientConnectionData->connectionSocket, formattedMessage, sizeof(formattedMessage), 0);
        }
    }
}

void receiveAndSendMessages(const SOCKET connectionSocket, const char* username) {
    ClientConnectionData* clientConnectionData = (ClientConnectionData*)malloc(sizeof(ClientConnectionData));
    clientConnectionData->connectionSocket = connectionSocket;
    clientConnectionData->username = (char*)malloc(strlen(username) + 1);
    strcpy(clientConnectionData->username, username);
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE) receiveAndPrintMessages, (LPVOID)(clientConnectionData), 0, 0);
    sendMessage(clientConnectionData);
}