#include <stdio.h>
#include <winsock2.h>

SOCKET connections[100];
int counter = 0;

void ClientHandler(int index) {
    char msg[256];
    while (1) {
        recv(connections[index], msg, sizeof(msg), 0);
        for (int i = 0; i < counter; i++) {
            if (i == index) {
                continue;
            }

            send(connections[i], msg, sizeof(msg), 0);
        }
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

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, 0);

    bind(sListen, (SOCKADDR*)&addr, addrSize);
    listen(sListen, SOMAXCONN);

    for (int i = 0; i < 100; i++) {
        SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addrSize);

        if (newConnection == 0) {
            puts("Error: Client cant connect to server");
            return -1;
        } else {
            puts("Client successfully connected!");
        }

        connections[i] = newConnection;
        counter++;

        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ClientHandler, (LPVOID)(i), 0, 0);
    }

    return 0;
}
