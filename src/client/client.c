#include "../../include/client/client.h"
#include "../../include/other/common.h"
#include "../../include/other/os_directives.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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
    }
    puts("Connected!");
    return EXIT_SUCCESS;
}

_Noreturn void* receiveAndPrintMessages(void* threadData) {
    const ClientConnectionData* clientConnectionData = (ClientConnectionData*)threadData;
    char message[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH + 4];
    while (1) {
        const int bytesReceived = recv(clientConnectionData->connectionSocket, message, sizeof(message), 0);
        if (bytesReceived > 0) {
            message[bytesReceived] = '\0';
            message[strcspn(message, "\n")] = '\0';
            printf("\r                                                                      ");
            printf("\r%s\n", message);
            printf("[%s] ", clientConnectionData->username);
            fflush(stdout);
        }
    }
}

void sendMessage(const ClientConnectionData* clientConnectionData) {
    char message[MAX_MESSAGE_LENGTH];
    while (1) {
        printf("[%s] ", clientConnectionData->username);
        fflush(stdout);
        scanf("%s", message);
        char formattedMessage[MAX_MESSAGE_LENGTH + MAX_USERNAME_LENGTH + 4];
        message[strcspn(message, "\n")] = '\0';
        snprintf(formattedMessage, sizeof(formattedMessage), "[%s] %s", clientConnectionData->username, message);
        send(clientConnectionData->connectionSocket, formattedMessage, sizeof(formattedMessage), 0);
    }
}

void receiveAndSendMessages(const SOCKET connectionSocket, const char* username) {
    ClientConnectionData* clientConnectionData = (ClientConnectionData*)malloc(sizeof(ClientConnectionData));
    clientConnectionData->connectionSocket = connectionSocket;
    clientConnectionData->username = (char*)malloc(strlen(username) + 1);
    strcpy(clientConnectionData->username, username);

#ifdef _WIN32
    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)receiveAndPrintMessages, (LPVOID)(clientConnectionData), 0, 0);
#elif unix
    pthread_t id;
    pthread_create(&id, NULL, receiveAndPrintMessages, clientConnectionData);
#endif

    sendMessage(clientConnectionData);
}