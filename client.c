#include <stdio.h>
#include <winsock2.h>
#include <unistd.h>

SOCKET connection;

void ClientHandler() {
    char msg[256];
    while (1) {
        recv(connection, msg, sizeof(msg), 0);
        puts(msg);
    }
}

int main(int argc, char* argv[]) {
    struct WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if (WSAStartup(DLLVersion, &wsaData) != 0) {
        int error = WSAGetLastError();
        printf("Error: %d", error);
        return error;
    }

    SOCKADDR_IN addr;
    int addrSize = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;

    connection = socket(AF_INET, SOCK_STREAM, 0);

    if (connect(connection, (SOCKADDR*)&addr, addrSize) != 0) {
        puts("Error: Failed connect to server");
        return -1;
    } else {
        puts("Connected!");
    }

    CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ClientHandler, 0, 0, 0);

    char msg[256];
    while (1) {
        fgets(msg, 256, stdin);
        send(connection, msg, sizeof(msg), 0);
        sleep(1);
    }
}